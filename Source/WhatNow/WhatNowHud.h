// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "WhatNowHud.generated.h"


UCLASS(config = Game)
class AWhatNowHud : public AHUD
{
	GENERATED_BODY()

public:
	AWhatNowHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	UPROPERTY()
	float move;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
