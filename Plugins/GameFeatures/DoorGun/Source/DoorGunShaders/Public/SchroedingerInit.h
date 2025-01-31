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

IMPLEMENT_GLOBAL_SHADER(FSchroedingerInit, "/DoorGunShadersShaders/Schroedinger.usf", "InitParticleSystem", SF_Compute);