// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Modules/ModuleManager.h"

class FNearbyConnectionsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
