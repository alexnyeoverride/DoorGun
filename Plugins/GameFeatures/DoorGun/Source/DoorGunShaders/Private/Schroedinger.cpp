#include "DoorGunShaders/Public/Schroedinger.h"
#include "SchroedingerInterface.h"
#include "DoorGunShaders/Public/SchroedingerInit.h"


constexpr int16 GGrid_Side_Length = 32;
constexpr int16 GGrid_Height = 512;


TRefCountPtr<IPooledRenderTarget> FSchroedingerInterface::PersistentPing = nullptr;
TRefCountPtr<IPooledRenderTarget> FSchroedingerInterface::PersistentPong = nullptr;
bool FSchroedingerInterface::PingPong = false;

// TODO call initialization shader from GameMode::BeginPlay and call Schroedinger from ... Tick?
// TODO vertex and pixel shaders.

void FSchroedingerInterface::Initialize(FRHICommandListImmediate& RHICmdList)
{
	FRDGBuilder GraphBuilder(RHICmdList);

	const FSchroedinger::FPermutationDomain PermutationVector;
	const auto ComputeShader = TShaderMapRef<FSchroedingerInit>(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);

	const auto TextureDesc = FRDGTextureDesc::Create3D(
		FIntVector(GGrid_Side_Length, GGrid_Side_Length, GGrid_Height),
		PF_G32R32F, // TODO: check this
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV
	);

	// These are temporary FRDGTextureRefs.  Convert them to TRefCountPtr<IPooledRenderTarget> via QueueTextureExtraction.
	// Then use RegisterExternalTexture each frame.
	const auto PingRef = GraphBuilder.CreateTexture(TextureDesc, TEXT("SchroedingerPing"));
	const auto PongRef = GraphBuilder.CreateTexture(TextureDesc, TEXT("SchroedingerPong"));
	GraphBuilder.QueueTextureExtraction(PingRef, &PersistentPing);
	GraphBuilder.QueueTextureExtraction(PongRef, &PersistentPong);
	
	const auto PassParameters = GraphBuilder.AllocParameters<FSchroedingerInit::FParameters>();
	PassParameters->Ping = GraphBuilder.CreateUAV(PingRef);
	PassParameters->Pong = GraphBuilder.CreateUAV(PongRef);
	
	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("SchroedingerInit"),
		ComputeShader,
		PassParameters,
		FIntVector(
			GGrid_Side_Length / 8,
			GGrid_Side_Length / 8,
			GGrid_Height / 8
		)
	);

	GraphBuilder.Execute();
}


void FSchroedingerInterface::Dispatch(
	FRHICommandListImmediate& RHICmdList,
	const float DeltaTime,
	const TArray<FTransform>& Transforms
)
{
	FRDGBuilder GraphBuilder(RHICmdList);

	const FSchroedinger::FPermutationDomain PermutationVector;
	const auto ComputeShader = TShaderMapRef<FSchroedinger>(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);

	// Register external textures with the current RDG.
	// Required to make persistent textures compatible with this frame's graph.
	const auto Ping = GraphBuilder.RegisterExternalTexture(PersistentPing);
	const auto Pong = GraphBuilder.RegisterExternalTexture(PersistentPong);
	
	// TODO: set up compute -> vertex -> pixel graph
	const auto ComputeParameters = GraphBuilder.AllocParameters<FSchroedinger::FParameters>();
	
	ComputeParameters->DeltaTime = DeltaTime;
	ComputeParameters->ReadTexture = GraphBuilder.CreateSRV(PingPong ? Ping : Pong);
	ComputeParameters->WriteTexture = GraphBuilder.CreateUAV(PingPong ? Pong : Ping);
	PingPong = !PingPong;

	TResourceArray<FMatrix> TransformMatrices;
	TransformMatrices.Reserve(Transforms.Num());
	for (const FTransform& Transform : Transforms)
	{
		TransformMatrices.Add(Transform.ToMatrixWithScale());
	}

	const auto TransformBuffer = CreateStructuredBuffer(
		GraphBuilder,
		TEXT("InputTransforms"),
		sizeof(FMatrix),
		Transforms.Num(),
		&TransformMatrices,
		sizeof(FMatrix) * Transforms.Num()
	);
	// TODO: actually a param for the vertex pass
	//ComputeParameters->InputTransforms = GraphBuilder.CreateSRV(TransformBuffer);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("SchroedingerDispatch"),
		ComputeShader,
		ComputeParameters,
		FIntVector(GGrid_Side_Length / 8, GGrid_Side_Length / 8, GGrid_Height / 8)
	);

	// TODO const auto VertexShader =

	GraphBuilder.Execute();
}


void FSchroedingerInterface::Initialize()
{
	ENQUEUE_RENDER_COMMAND(InitializeSchroedinger)(
		[](FRHICommandListImmediate& RHICmdList)
		{
			Initialize(RHICmdList);					
		}
	);
}

void FSchroedingerInterface::Dispatch(const float DeltaTime, const TArray<FTransform>& Transforms)
{
	ENQUEUE_RENDER_COMMAND(SchroedingerDispatch)(
		[DeltaTime, Transforms](FRHICommandListImmediate& RHICmdList)
		{
			Dispatch(RHICmdList, DeltaTime, Transforms);					
		}
	);
}
