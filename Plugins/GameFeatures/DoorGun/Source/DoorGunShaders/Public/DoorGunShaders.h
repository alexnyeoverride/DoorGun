#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class DOORGUNSHADERS_API FDoorGunShadersModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};