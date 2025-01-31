#include "DoorGunShaders/Public/Schroedinger.h"


constexpr int16 GGrid_Side_Length = 32;
constexpr int16 GGrid_Height = 512;

FRDGTextureRef FSchroedingerInterface::Ping = nullptr;
FRDGTextureRef FSchroedingerInterface::Pong = nullptr;


// TODO call initialization shader from GameMode::BeginPlay and call Schroedinger from ... somewhere in the rendering
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

	Ping = GraphBuilder.CreateTexture(TextureDesc, TEXT("SchroedingerPing"));
	Pong = GraphBuilder.CreateTexture(TextureDesc, TEXT("SchroedingerPong"));

	if (ComputeShader.IsValid())
	{
		const auto PassParameters = GraphBuilder.AllocParameters<FSchroedingerInit::FParameters>();
		PassParameters->Ping = GraphBuilder.CreateUAV(Ping);
		PassParameters->Pong = GraphBuilder.CreateUAV(Pong);
		
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
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SchroedingerInit is invalid"));
	}

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

	// TODO: set up compute -> vertex -> pixel graph
	if (ComputeShader.IsValid())
	{
		// TODO other buffers

		const auto ComputeParameters = GraphBuilder.AllocParameters<FSchroedinger::FParameters>();
		
		ComputeParameters->DeltaTime = DeltaTime;
		ComputeParameters->NumTransforms = Transforms.Num();

		FRDGBufferRef TransformBuffer = CreateStructuredBuffer(
			GraphBuilder,
			TEXT("InputTransforms"),
			sizeof(FMatrix),
			Transforms.Num(),
			&Transforms, // TODO: map transforms to FMatrix via .ToMatrixWithScale()
			sizeof(FMatrix) * Transforms.Num()
		);

		FComputeShaderUtils::AddPass(
			GraphBuilder,
			RDG_EVENT_NAME("Schroedinger"),
			ComputeShader,
			ComputeParameters,
			FIntVector(GGrid_Side_Length / 8, GGrid_Side_Length / 8, GGrid_Height / 8)
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SchroedingerDispatch is invalid"));
	}

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
	// TODO: SceneDrawCompletion is sus.  The portal should be part of the scene draw.
	ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
		[DeltaTime, Transforms](FRHICommandListImmediate& RHICmdList)
		{
			Dispatch(RHICmdList, DeltaTime, Transforms);					
		}
	);
}
