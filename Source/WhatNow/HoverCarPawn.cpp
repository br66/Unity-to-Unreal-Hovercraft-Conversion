// Fill out your copyright notice in the Description page of Project Settings.

#include "WhatNow.h"
#include "HoverCarPawn.h"
#include "GameFramework/SpringArmComponent.h" // shouldn't springarmcomponent be in components folder?
#include "Components/ChildActorComponent.h" //why aren't the components all in one place?
#include "Engine/World.h" // i need to include this header to use UWorld or GetWorld(), no evidence that anyone online has to
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"

// warning ue4 needs forward slashes (/) contradicting vs default of backward slashes (\)

// Sets default values
AHoverCarPawn::AHoverCarPawn()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// SetupAttachment function in example doesn't fockin woik
	SpringArm->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	AllThrusters = CreateDefaultSubobject<UChildActorComponent>(TEXT("AllThrusters"));
	AllThrusters->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	Thruster1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Thruster1"));
	Thruster1->SetupAttachment(AllThrusters);
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
	Thrust2();
	//Thrust();
}

// Called to bind functionality to input
void AHoverCarPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AHoverCarPawn::Thrust()
{
	/* is there a way to get certain children components? find out later
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
		FVector downVector = (((i->GetUpVector()*-1) * traceLength) + i->GetComponentLocation());
		FCollisionQueryParams* traceParams = new FCollisionQueryParams();

		DrawDebugLine(GetWorld(), i->GetComponentLocation(), downVector, FColor::Cyan, false, -1.0f, 0, 4.3f);

		if (GetWorld()->LineTraceSingleByChannel(*hit, i->GetComponentLocation(), downVector, ECC_Visibility, *traceParams))
		{

			// i must be close to the ground or whatever is under me
			FVector downwardForce;
			float distancePercentage;

			distancePercentage = 1 - (hit->Distance / thrusterDistance);

			// how much pushing away from the ground should I do? (force)
			downwardForce = this->GetActorUpVector() * thrusterStrength * distancePercentage;

			/////////
			float vLength = (hit->Location - i->GetComponentLocation()).Size();
			float ifHover = vLength / traceLength;
			float lerp = FMath::Lerp(hoverForce, 0.0f, ifHover);

			FVector newForce = lerp * hit->ImpactNormal;
			/////////

			// take into consideration mass and deltatime, i dont have mass by default
			downwardForce *= (GetWorld()->GetDeltaSeconds() * GetMesh()->GetMass() * hoverForce);

			// apply *le force
			GetMesh()->AddForceAtLocation(downwardForce, i->GetComponentLocation() );
			
			UE_LOG(LogTemp, Warning, TEXT("%f"), newForce.Z);
		}
	}

	//FVector thrusterPosition = Thruster1->GetComponentLocation();*/
}

void AHoverCarPawn::Thrust2()
{
	// get all thrusters
	TArray<USceneComponent*> thrusterArray;
	AllThrusters->GetChildrenComponents(false, thrusterArray);

	// create a variable that will store information about the raycast hit
	FHitResult* hit = new FHitResult();

	// for each thruster
	for (USceneComponent* & i : thrusterArray)
	{
		// this may change the thrusters world space to local space relative to the mesh component's transform
		FVector startTrace = GetMesh()->GetComponentTransform().TransformPosition(i->GetComponentLocation());
		FVector endTrace = startTrace + FVector(0, 0, thrusterDistance);

		FCollisionQueryParams* traceParams = new FCollisionQueryParams();

		if (GetWorld()->LineTraceSingleByObjectType(*hit, startTrace, endTrace, ECC_MAX, *traceParams))
		{
			float idk1 = hit->Location.Z + thrusterStrength;
			float idk2 = idk1 - startTrace.Z;
			float idk3 = idk2 / (traceSmooth * 2);
			float idk3Clamped = FMath::Clamp(idk3, 0.0f, 1.0f);
			float idk4 = GetMesh()->GetMass() / hoverForce;
			float idk5 = idk4 * 980;
			float idk6 = idk5 / 4;
			float finalForceZ = idk6 * idk3Clamped;

			// judging by how much the z (up vector), this must have to do with the force: boosting the z to make it hover
			// float force = FMath::Clamp(((startTrace.Z - (hit->Location.Z + thrusterStrength))/(traceSmooth*2)),0.0f,1.0f);
			// taking into consideration the mass and, for some reason, the amount of thrusters. probably for some sort of
			// equalization between the thrusters, which was a problem in the first function
			// float mass = (((GetMesh()->GetMass()/hoverForce) * 980)/4);

			// float finalForce = force * mass;

			GetMesh()->AddForceAtLocation(FVector(0.0f,0.0f,finalForceZ), GetMesh()->GetComponentLocation());
		}
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Cyan, false, -1.0f, 0, 4.3f);
	}
}

// things that crash this fockin engin
// setting the skeletal mesh
// setting up attachments

// sometimes unreal will not show you the updates from the code in the editor
// because its such a great engine
// even when you refresh visual studio project, you may still not see the changes you've made
// you actually have to restart unreal editor, great

// award for most unstable engine, always crashing. sad!

// attachcomponent and setupattachment only work half the time