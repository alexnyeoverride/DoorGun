#include "DoorGunShaders/Public/DoorGunShaders.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "RHI.h"
#include "GlobalShader.h"
#include "RHICommandList.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "DoorGunShadersModule"


void FDoorGunShadersModule::StartupModule()
{
	// Maps virtual shader source directory to the plugin's actual shaders directory.
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(
		TEXT("DoorGun"))->GetBaseDir(),
		TEXT("DoorGunShaders/Private")
	);
	AddShaderSourceDirectoryMapping(TEXT("/DoorGunShadersShaders"), PluginShaderDir);
}

void FDoorGunShadersModule::ShutdownModule()
{
}


#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FDoorGunShadersModule, DoorGunShaders)