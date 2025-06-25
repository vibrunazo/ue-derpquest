// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Components/DerpSpringArmComponent.h"

void UDerpSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Cache our default rotation once the game starts
	DefaultRotation = GetComponentRotation();
}

void UDerpSpringArmComponent::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag,
                                                       float DeltaTime)
{
	// Perform a trace to detect collisions
	FHitResult HitResult;
	FVector Start = GetComponentLocation();
	FVector End = GetSocketLocation(SocketName);
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ProbeChannel);

	FRotator CurrentRotation = GetComponentRotation();
	if (HitResult.bBlockingHit)
	{
		// If we have a blocking hit, instead of moving the camera, rotate the arm up
		FRotator NewRotation = CurrentRotation + FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f);
		if (NewRotation.Pitch > MaxPitchAngle)
		{
			NewRotation.Pitch = MaxPitchAngle;
		}
		SetWorldRotation(NewRotation);
	}
	else
	{
		// NO COLLISION: Smoothly interpolate back to our stored default rotation
		// FRotator NewRotation = CurrentRotation + FRotator(-RotationSpeed * DeltaTime, 0.0f, 0.0f);
		// if (NewRotation.Pitch > DefaultRotation.Pitch)
		// {
		// 	NewRotation.Pitch = DefaultRotation.Pitch;
		// }
		// SetWorldRotation(NewRotation);
		// --- STATE: NOT BLOCKED (Potentially Returning) ---
		// The current position is clear, but is the path back to default clear?

		// --- "Look-Ahead" Trace at DEFAULT rotation ---
		// This trace checks if returning to the default angle would be blocked.
		FHitResult DefaultTraceHit;
		FVector DefaultTraceEnd = End - FVector::UpVector * MarginDownwards;
		GetWorld()->LineTraceSingleByChannel(DefaultTraceHit, Start, DefaultTraceEnd, ProbeChannel);

		if (DefaultTraceHit.bBlockingHit)
		{
			// --- STATE: IDLE AT OBSTACLE ---
			// The current position is fine, but the default position is blocked.
			// DO NOTHING. Stay at the current, raised angle. This prevents the zig-zag.
		}
		else
		{
			FRotator NewRotation = CurrentRotation + FRotator(-RotationSpeed * DeltaTime, 0.0f, 0.0f);
			if (NewRotation.Pitch > DefaultRotation.Pitch)
			{
				NewRotation.Pitch = DefaultRotation.Pitch;
			}
			SetWorldRotation(NewRotation);
		}
	}
	
	Super::UpdateDesiredArmLocation(bDoTrace, bDoLocationLag, bDoRotationLag, DeltaTime);
	
}
