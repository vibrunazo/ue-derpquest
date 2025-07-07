// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/DerpPlayerPawn.h"

#include "Actor/Components/DerpSpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Char/DerpCharacter.h"
#include "Game/DerpPlayerController.h"

// Sets default values
ADerpPlayerPawn::ADerpPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the root component
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneRoot;

	// Create the camera boom component
	CameraBoom = CreateDefaultSubobject<UDerpSpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create the camera component
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ADerpPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (auto DerpController = Cast<ADerpPlayerController>(GetController()))
		TargetChar = DerpController->ControlledUnits[0];
	
}

// Called every frame
void ADerpPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetChar && bShouldFollow)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = TargetChar->GetActorLocation();
        
		FVector NewLocation = FMath::VInterpTo(
			CurrentLocation,
			TargetLocation,
			DeltaTime,
			LerpSpeed
		);
        
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void ADerpPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

