#include "DoorGunShaders/Public/DoorGunShaders.h"

#include "SchroedingerInterface.h"
#include "Interfaces/IPluginManager.h"


void FDoorGunShadersModule::StartupModule()
{
	// Maps virtual shader source directory to the plugin's actual shader directory.
	const auto PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(
		TEXT("DoorGun"))->GetBaseDir(),
		TEXT("Source/DoorGunShaders/Private")
	);
	AddShaderSourceDirectoryMapping(TEXT("/DoorGunShadersShaders"), PluginShaderDir);
}

void FDoorGunShadersModule::ShutdownModule()
{
	FSchroedingerInterface::CleanUp();
}


IMPLEMENT_MODULE(FDoorGunShadersModule, DoorGunShaders)