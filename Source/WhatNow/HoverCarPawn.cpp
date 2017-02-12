// Fill out your copyright notice in the Description page of Project Settings.

#include "WhatNow.h"
#include "HoverCarPawn.h"
#include "GameFramework/SpringArmComponent.h" // shouldn't springarmcomponent be in components folder?
#include "Components/ChildActorComponent.h" //why aren't the components all in one place?
#include "Engine/World.h" // i need to include this header to use UWorld or GetWorld(), no evidence that anyone online has to
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine.h"

// warning ue4 needs forward slashes (/) contradicting vs default of backward slashes (\)

// Sets default values
AHoverCarPawn::AHoverCarPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// SetupAttachment function in example doesn't fockin woik
	SpringArm->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	AllThrusters = CreateDefaultSubobject<UChildActorComponent>(TEXT("AllThrusters"));

	Thruster1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster1"));
	Thruster1->SetupAttachment(AllThrusters);
	Thruster1->AttachTo(AllThrusters);
	Thruster1->AttachToComponent(AllThrusters, FAttachmentTransformRules::KeepRelativeTransform);

	Thruster2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster2"));
	Thruster2->AttachToComponent(AllThrusters, FAttachmentTransformRules::KeepRelativeTransform);

	Thruster3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster3"));
	Thruster3->AttachToComponent(AllThrusters, FAttachmentTransformRules::KeepRelativeTransform);
	
	Thruster4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster4"));
	Thruster4->AttachToComponent(AllThrusters, FAttachmentTransformRules::KeepRelativeTransform);

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;
	Camera->bEditableWhenInherited = true;
	
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
	Thrust();
}

// Called to bind functionality to input
void AHoverCarPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AHoverCarPawn::Thrust()
{
	float thrusterStrength = 10;
	float thrusterDistance = 40;

	// is there a way to get certain children components? find out later
	// might want to check their class before the for loop so I only affect the
	// thrusters just in case I add more child components that aren't thrusters
	// or put all thrusters under one parent
	TArray<USceneComponent*> thrusterArray;
	AllThrusters->GetChildrenComponents(false, thrusterArray);
	
	// equivalent to RaycastHit hit in Unity
	FHitResult* hit = new FHitResult();

	// for every scene component ( as 'i') in thruster array (c++ 11 for loop)
	for (USceneComponent* & i : thrusterArray)
	{
		//if (i->GetClass()->IsChildOf(YourClass::StaticClass) {}
		//AActor* thruster = i->GetOwner();	
		FVector downVector = (((i->GetUpVector() * -1) * 2) + i->GetComponentLocation());
		FCollisionQueryParams* traceParams = new FCollisionQueryParams();

		if (GetWorld()->LineTraceSingleByChannel(*hit, i->GetComponentLocation(), downVector, ECC_Visibility, *traceParams))
		{
			// i must be close to the ground or whatever is under me

			FVector downwardForce;
			float distancePercentage;

			distancePercentage = 1 - (hit->Distance / thrusterDistance);

			// how much pushing away from the ground should I do? (force)
			downwardForce = this->GetActorUpVector() * thrusterStrength * distancePercentage;

			// take into consideration mass and deltatime, i dont have mass by default
			downwardForce *= (GetWorld()->GetDeltaSeconds() * 100);

			// apply *le force
			GetMesh()->AddForceAtLocation(downwardForce, i->GetComponentLocation());
		}
	}

	//FVector thrusterPosition = Thruster1->GetComponentLocation();

}


//things that crash this fockin engin
// setting the skeletal mesh
// setting up attachments

// sometimes unreal will not show you the updates from the code in the editor
// because its such a great engine
// even when you refresh visual studio project, you may still not see the changes you've made
// you actually have to restart unreal editor, great

// award for most unstable engine, always crashing. sad!

// attachcomponent and setupattachment only work half the time