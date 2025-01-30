#include "DoorGunShaders/Public/Schroedinger.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphEvent.h"
#include "ShaderParameterStruct.h"

DECLARE_STATS_GROUP(TEXT("Schroedinger"), STATGROUP_Schroedinger, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("Schroedinger Execute"), STAT_Schroedinger_Execute, STATGROUP_Schroedinger);

// This class carries our parameter declarations and acts as the bridge between cpp and HLSL.
class DOORGUNSHADERS_API FSchroedinger : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedinger);
	SHADER_USE_PARAMETER_STRUCT(FSchroedinger, FGlobalShader);

	// TODO
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, DeltaTime)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<FMatrix>, SharedTransforms)
	END_SHADER_PARAMETER_STRUCT()
};

// TODO vertex and pixel shaders

IMPLEMENT_GLOBAL_SHADER(FSchroedinger, "/DoorGunShadersShaders/Schroedinger.usf", "Schroedinger", SF_Compute);

void FSchroedingerInterface::DispatchRenderThread(FRHICommandListImmediate& RHICmdList, FSchroedingerDispatchParams Params, TFunction<void(int OutputVal)> AsyncCallback) {
	FRDGBuilder GraphBuilder(RHICmdList);

	SCOPE_CYCLE_COUNTER(STAT_Schroedinger_Execute);
	DECLARE_GPU_STAT(Schroedinger)
	RDG_EVENT_SCOPE(GraphBuilder, "Schroedinger");
	RDG_GPU_STAT_SCOPE(GraphBuilder, Schroedinger);

	const FSchroedinger::FPermutationDomain PermutationVector;
	const auto ComputeShader = TShaderMapRef<FSchroedinger>(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);

	if (ComputeShader.IsValid())
	{
		// TODO
	}

	GraphBuilder.Execute();
}