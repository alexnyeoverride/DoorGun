#include "DoorGunShaders/Public/Schroedinger.h"
#include "RenderGraphBuilder.h"
#include "ShaderParameterStruct.h"

class DOORGUNSHADERS_API FSchroedinger : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedinger);
	SHADER_USE_PARAMETER_STRUCT(FSchroedinger, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		// Inputs from the CPU at initialization /////////////////////////////////
		// initialize to false, for Ping as the start texture
		SHADER_PARAMETER_RDG_BUFFER_UAV(bool, PingPong)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWTexture3D<float2>, Ping)
	
		// Inputs from CPU each frame ////////////////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_SRV(float, DeltaTime)
		// dynamic array of all portals' locations and orientations as transforms
		SHADER_PARAMETER_RDG_BUFFER_SRV(RWBuffer<Float4x4>, InputTransforms)
		SHADER_PARAMETER_RDG_BUFFER_SRV(int, NumTransforms)
	
		// Outputs to vertex shader //////////////////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_SRV(RWBuffer<float3>, TriangleList)
		SHADER_PARAMETER_RDG_BUFFER_SRV(RWBuffer<float>, Phases)
	
		// Outputs all the way to pixel shader ///////////////////////////////////
		SHADER_PARAMETER_RDG_BUFFER_SRV(RWBuffer<float>, Probabilities)
	END_SHADER_PARAMETER_STRUCT()
};

// TODO vertex and pixel shaders

IMPLEMENT_GLOBAL_SHADER(FSchroedinger, "/DoorGunShadersShaders/Schroedinger.usf", "Schroedinger", SF_Compute);

void FSchroedingerInterface::DispatchRenderThread(FRHICommandListImmediate& RHICmdList, FSchroedingerDispatchParams Params, TFunction<void(int OutputVal)> AsyncCallback) {
	FRDGBuilder GraphBuilder(RHICmdList);

	const FSchroedinger::FPermutationDomain PermutationVector;
	const auto ComputeShader = TShaderMapRef<FSchroedinger>(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);

	if (ComputeShader.IsValid())
	{
		// TODO: initialize Ping texture with gaussian noise / sinusoidal noise
		// TODO: set up compute -> vertex -> pixel graph
		// TODO: how do I initialize the ping texture once, but continuously update DT and input transforms
	}

	GraphBuilder.Execute();
}