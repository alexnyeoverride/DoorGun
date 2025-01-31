#pragma once

#include "GenericPlatform/GenericPlatformMisc.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"

class DOORGUNSHADERS_API FSchroedingerInit : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedingerInit);
	SHADER_USE_PARAMETER_STRUCT(FSchroedingerInit, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture3D<float2>, Ping)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture3D<float2>, Pong)
	END_SHADER_PARAMETER_STRUCT()
};

IMPLEMENT_GLOBAL_SHADER(FSchroedingerInit, "/DoorGunShadersShaders/Schroedinger.usf", "SchroedingerInit", SF_Compute);


class DOORGUNSHADERS_API FSchroedinger : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedinger);
	SHADER_USE_PARAMETER_STRUCT(FSchroedinger, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		// Inputs from CPU each frame ////////////////////////////////////////////
		SHADER_PARAMETER(float, DeltaTime)

		// TODO: move to vertex shader
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

IMPLEMENT_GLOBAL_SHADER(FSchroedinger, "/DoorGunShadersShaders/Schroedinger.usf", "Schroedinger", SF_Compute);


class DOORGUNSHADERS_API FSchroedingerInterface
{
public:
	static void Initialize();
	static void Dispatch(
		const float DeltaTime, const TArray<FTransform>& Transforms
	);

private:
	static void Initialize(FRHICommandListImmediate& RHICmdList);
	static void Dispatch(
		FRHICommandListImmediate& RHICmdList,
		const float DeltaTime, const TArray<FTransform>& Transforms
	);

	static FRDGTextureRef Ping;
	static FRDGTextureRef Pong;
};