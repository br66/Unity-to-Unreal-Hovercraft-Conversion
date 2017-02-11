// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Pawn.h"
#include "HoverCarPawn.generated.h"

class UCameraComponent; // some fockin standards
class USpringArmComponent;
class UChildActorComponent;
class UInputComponent;

UCLASS() // the amount of spaces between #include and UCLASS() matters for some reason
class AHoverCarPawn : public APawn
{
	GENERATED_BODY() // some fockin standard
		
public:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* Camera;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		UChildActorComponent* Thruster1;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		UChildActorComponent* Thruster2;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		UChildActorComponent* Thruster3;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		UChildActorComponent* Thruster4;


public:
	// Sets default values for this pawn's properties
	AHoverCarPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//
	void Thrust();
	
public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; } 
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
};
