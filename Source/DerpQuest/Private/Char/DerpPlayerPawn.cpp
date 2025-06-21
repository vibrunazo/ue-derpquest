// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/DerpPlayerPawn.h"

#include "Char/DerpCharacter.h"
#include "Game/DerpPlayerController.h"

// Sets default values
ADerpPlayerPawn::ADerpPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	if (TargetChar)
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

