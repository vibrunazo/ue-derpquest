// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DerpPlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class DERPQUEST_API ADerpPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Touch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	/** Directional Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DirectionalMoveAction;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;
	/** Saved location of the character movement destination */
	FVector CachedDestination;
	/** Time that the click input has been pressed */
	float FollowTime = 0.0f;
	/** True when directional movement input (WASD/gamepad) is being used */
	bool bIsDirectionalMovementActive = false;

public:

	/** Constructor */
	ADerpPlayerController();

	
protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	/** Gameplay initialization */
	virtual void BeginPlay();

	/** Input handlers */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void OnDirectionalMoveTriggered(const FInputActionValue& Value);
	void OnDirectionalMoveReleased();
	
};
