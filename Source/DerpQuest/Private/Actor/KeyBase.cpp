// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/KeyBase.h"

// Sets default values
AKeyBase::AKeyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeyBase::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetActorLocation();
}

// Called every frame
void AKeyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		// If there's a target actor, update the target location to the actor's location plus offset
		if (TargetActor && TargetActor->IsValidLowLevel())
		{
			TargetLocation = TargetActor->GetActorLocation();
		}
		
		FVector CurrentLocation = GetActorLocation();
		// Calculate the new location using VInterpTo for smooth movement
		FVector NewLocation = FMath::VInterpTo(
			CurrentLocation,
			TargetLocation + TargetOffset,
			DeltaTime,
			MoveSpeed
		);

		// Check if we've reached close enough to the target
		if (FVector::Distance(NewLocation, TargetLocation) >= 1.0f)
		{
			// Update the actor's location
			SetActorLocation(NewLocation);
			// bShouldMove = false;
		}
	}
}

