// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WhatNow.h"
#include "WhatNowHud.h"
#include "WhatNowPawn.h"
#include "GameFramework/WheeledVehicle.h"
#include "RenderResource.h"
#include "Shader.h"
#include "Engine/Canvas.h"
#include "Vehicles/WheeledVehicleMovementComponent.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "Engine.h"

// Needed for VR Headset
#if HMD_MODULE_INCLUDED
#include "IHeadMountedDisplay.h"
#endif // HMD_MODULE_INCLUDED 

#define LOCTEXT_NAMESPACE "VehicleHUD"

AWhatNowHud::AWhatNowHud()
{
	// getting the font, setting it to variable
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void AWhatNowHud::DrawHUD()
{
	Super::DrawHUD();

	// Calculate ratio from 720p
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;

	bool bWantHUD = true;
#if HMD_MODULE_INCLUDED
	if (GEngine->HMDDevice.IsValid() == true)
	{
		bWantHUD = GEngine->HMDDevice->IsStereoEnabled();
	}
#endif // HMD_MODULE_INCLUDED
	// We dont want the onscreen hud when using a HMD device	
	if (bWantHUD == true)
	{
		// Get our vehicle so we can check if we are in car. If we are, we don't want onscreen HUD

		// how do I describe this to another person?
		AWhatNowPawn* Vehicle = Cast<AWhatNowPawn>(GetOwningPawn());
		if ((Vehicle != nullptr) && (Vehicle->bInCarCameraActive == false))
		{
			move += 0.1f;

			FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);

			// Speed
			FCanvasTextItem SpeedTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 455), Vehicle->SpeedDisplayString, HUDFont, FLinearColor::White);
			SpeedTextItem.Scale = ScaleVec;
			Canvas->DrawItem(SpeedTextItem);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), SpeedTextItem.Position.X);
			
			FCanvasTextItem CollisionItem1(FVector2D(HUDXRatio * 10.0f, HUDYRatio * 10.0f), Vehicle->TestDisplayString, HUDFont, FLinearColor::White);
			CollisionItem1.Scale = ScaleVec;
			Canvas->DrawItem(CollisionItem1);
			//UE_LOG(LogTemp, Warning, TEXT("%f :: %f"), CollisionItem1.DrawnSize.X, CollisionItem1.DrawnSize.Y);

			FCanvasTextItem CollisionItem2(FVector2D(HUDXRatio * move, HUDYRatio * 10.0f), Vehicle->TestDisplayString, HUDFont, FLinearColor::White);
			CollisionItem2.Scale = ScaleVec;
			Canvas->DrawItem(CollisionItem2);
			//UE_LOG(LogTemp, Warning, TEXT("%f :: %f"), CollisionItem2.DrawnSize.X, CollisionItem2.DrawnSize.Y);

			// Gear
			FCanvasTextItem GearTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f), Vehicle->GearDisplayString, HUDFont, Vehicle->bInReverseGear == false ? Vehicle->GearDisplayColor : Vehicle->GearDisplayReverseColor);
			GearTextItem.Scale = ScaleVec;
			Canvas->DrawItem(GearTextItem);

			/* collision
			if ((CollisionItem1.Position.X > CollisionItem2.Position.X + CollisionItem2.DrawnSize.X) || (CollisionItem2.Position.X > CollisionItem1.Position.X + CollisionItem1.DrawnSize.X) ||
				(CollisionItem1.Position.Y > CollisionItem2.Position.Y + CollisionItem2.DrawnSize.Y) || (CollisionItem2.Position.Y > CollisionItem1.Position.Y + CollisionItem1.DrawnSize.Y))
			{
				UE_LOG(LogTemp, Warning, TEXT("REKT"));
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("BOOOOOOOOOOOOOOOOOOOOST"));
				*/
		}
	}
}


#undef LOCTEXT_NAMESPACE
