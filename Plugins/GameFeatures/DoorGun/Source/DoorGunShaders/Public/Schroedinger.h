#pragma once

#include "GenericPlatform/GenericPlatformMisc.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"


class DOORGUNSHADERS_API FSchroedinger : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSchroedinger);
	SHADER_USE_PARAMETER_STRUCT(FSchroedinger, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(float, DeltaTime)
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture3D<float2>, ReadTexture)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture3D<float2>, WriteTexture)
		SHADER_PARAMETER(bool, PingPong)
	END_SHADER_PARAMETER_STRUCT()
};

IMPLEMENT_GLOBAL_SHADER(FSchroedinger, "/DoorGunShadersShaders/Schroedinger.usf", "Schroedinger", SF_Compute);