#include "DoorGunShaders/Public/Schroedinger.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"


constexpr int16 GGrid_Side_Length = 32;
constexpr int16 GGrid_Height = 512;


class DOORGUNSHADERS_API FSchroedinger : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedinger);
	SHADER_USE_PARAMETER_STRUCT(FSchroedinger, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		// TODO move to initialization shader
		// Inputs from the CPU at initialization /////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWTexture3D<float2>, Ping)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWTexture3D<float2>, Pong)
	
		// Inputs from CPU each frame ////////////////////////////////////////////
		SHADER_PARAMETER(float, DeltaTime)
		// dynamic array of all portals' locations and orientations as transforms
		SHADER_PARAMETER_RDG_BUFFER_SRV(RWBuffer<Float4x4>, InputTransforms)
		SHADER_PARAMETER(int, NumTransforms)
	
		// Outputs to vertex shader //////////////////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float3>, TriangleList)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Phases)
	
		// Outputs all the way to pixel shader ///////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Probabilities)
	END_SHADER_PARAMETER_STRUCT()
};

// TODO call initialization shader from GameMode::BeginPlay and call Schroedinger from GameMode::Tick
// TODO initialization shader // TODO it initializes the size of the 3D buffer as 32x32x512 // this should be the same buffer used by Schroedinger
IMPLEMENT_GLOBAL_SHADER(FSchroedinger, "/DoorGunShadersShaders/Schroedinger.usf", "Schroedinger", SF_Compute);
// TODO vertex and pixel shaders.  Can these be wired up automatically from Schroedinger or does the CPU have to control the sequence?

// TODO is this called every frame or just once?  Where do I update values from?
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