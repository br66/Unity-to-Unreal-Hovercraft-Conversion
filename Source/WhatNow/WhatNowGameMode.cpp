// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WhatNow.h"
#include "WhatNowGameMode.h"
#include "HoverCarPawn.h"
#include "WhatNowHud.h"

AWhatNowGameMode::AWhatNowGameMode()
{
	DefaultPawnClass = AHoverCarPawn::StaticClass();
	HUDClass = AWhatNowHud::StaticClass();
	//WhatNowHUD = Cast<AWhatNowHud>(WhatNowHUD);
}
