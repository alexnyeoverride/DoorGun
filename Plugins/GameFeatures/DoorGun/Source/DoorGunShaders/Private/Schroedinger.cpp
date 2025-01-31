#include "DoorGunShaders/Public/Schroedinger.h"


constexpr int16 GGrid_Side_Length = 32;
constexpr int16 GGrid_Height = 512;


// TODO call initialization shader from GameMode::BeginPlay and call Schroedinger from GameMode::Tick
// TODO vertex and pixel shaders.

void FSchroedingerInterface::Initialize(FRHICommandListImmediate& RHICmdList)
{
	FRDGBuilder GraphBuilder(RHICmdList);

	const FSchroedinger::FPermutationDomain PermutationVector;
	const auto ComputeShader = TShaderMapRef<FSchroedingerInit>(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);

	if (ComputeShader.IsValid())
	{
		// TODO init the size of the 3D buffer as 32x32x512
		// Call the compute shader
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

	// TODO const auto VertexShader =

	GraphBuilder.Execute();
}


void FSchroedingerInterface::Initialize()
{
	// TODO: SceneDrawCompletion is sus.  The portal should be part of the scene draw.
	ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
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
