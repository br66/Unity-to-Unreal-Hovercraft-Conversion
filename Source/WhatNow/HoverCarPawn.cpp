// Fill out your copyright notice in the Description page of Project Settings.

#include "WhatNow.h"
#include "HoverCarPawn.h"
#include "GameFramework/SpringArmComponent.h" // shouldn't springarmcomponent be in components folder?
#include "Components/ChildActorComponent.h" //why aren't the components all in one place?

// warning ue4 needs forward slashes (/) contradicting vs default of backward slashes (\)

// Sets default values
AHoverCarPawn::AHoverCarPawn()
{
	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));

	//thrusters = CreateDefaultSubobject<FTransform>(TEXT("thrusters0"));
	Thruster1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster1"));
	Thruster2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster2"));
	Thruster3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster3"));
	Thruster4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster4"));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoverCarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoverCarPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHoverCarPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AHoverCarPawn::Thrust()
{
	//float strength;
	//float distance;
	
	// array of positions
	//FTransform thrusters[4];
}
