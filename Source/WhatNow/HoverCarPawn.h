// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Pawn.h"
#include "HoverCarPawn.generated.h"

class UCameraComponent; // some fockin standard
class USpringArmComponent;
class UChildActorComponent;
class UInputComponent;
class UWorld;
//class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS() // the amount of spaces between #include and UCLASS() matters for some reason, no it doesn't this engine is just stupid
class AHoverCarPawn : public APawn
{
	GENERATED_BODY() // some fockin standard
		
public:
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(Category = Thruster, VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* AllThrusters;

	UPROPERTY(Category = Thruster, VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* Thruster1;

	UPROPERTY(Category = Thruster, VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* Thruster2;

	UPROPERTY(Category = Thruster, VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* Thruster3;

	UPROPERTY(Category = Thruster, VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* Thruster4;

	UPROPERTY(Category = Thruster, EditAnywhere, BlueprintReadWrite)
	float thrusterStrength = 200.0f;
	UPROPERTY(Category = Thruster, EditAnywhere, BlueprintReadWrite)
	float thrusterDistance = -1000.0f;
	UPROPERTY(Category = Thruster, EditAnywhere, BlueprintReadWrite)
	float traceLength = 0.0f;
	UPROPERTY(Category = Thruster, EditAnywhere, BlueprintReadWrite)
	float hoverForce = 0.7f;
	UPROPERTY(Category = Thruster, EditAnywhere, BlueprintReadWrite)
	float traceSmooth = 20.0f;


public:
	// Sets default values for this pawn's properties
	AHoverCarPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Activates Thrusters, called in Tick functions
	void Thrust();

	void Thrust2();
	
public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; } 
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	UStaticMeshComponent* GetMesh() const { return Mesh; }
};
