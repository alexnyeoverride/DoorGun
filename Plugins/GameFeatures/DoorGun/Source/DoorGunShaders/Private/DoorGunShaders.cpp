#include "DoorGunShaders/Public/DoorGunShaders.h"
#include "Interfaces/IPluginManager.h"


void FDoorGunShadersModule::StartupModule()
{
	// Maps virtual shader source directory to the plugin's actual shader directory.
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(
		TEXT("DoorGun"))->GetBaseDir(),
		TEXT("DoorGunShaders/Private")
	);
	AddShaderSourceDirectoryMapping(TEXT("/DoorGunShadersShaders"), PluginShaderDir);
}

void FDoorGunShadersModule::ShutdownModule()
{
}


IMPLEMENT_MODULE(FDoorGunShadersModule, DoorGunShaders)