// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "DerpSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class DERPQUEST_API UDerpSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	
	// Add any public properties you might need for your rotation logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraCollision")
	float RotationSpeed = 50.0f;

	// The maximum pitch we'll allow the camera to rotate up to, to prevent it from flipping over
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraCollision")
	float MaxPitchAngle = -20.0f;
	// Error Margin to check downwards before rotating back down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraCollision")
	float MarginDownwards = 500.0f;
	
private:
	// Variable to store the fixed, default rotation of the camera arm
	FRotator DefaultRotation;

protected:
	virtual void BeginPlay() override;
	
	// Add any private properties you might need for your rotation logic
	/** Updates the desired arm location, calling BlendLocations to do the actual blending if a trace is done */
	virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime) override;


};
