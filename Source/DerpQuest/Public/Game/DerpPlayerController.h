// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DerpPlayerController.generated.h"

class ADerpCharacter;
struct FInputActionValue;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlledUnitsChanged);

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

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnControlledUnitsChanged OnControlledUnitsChanged;

	/** Constructor */
	ADerpPlayerController();

	/** Currently controlled unit list */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<ADerpCharacter*> ControlledUnits;

	
protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	/** Gameplay initialization */
	virtual void BeginPlay();

	/** Select all units with the "Player" tag */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SelectAllPlayerUnits();
	
	/** Move the given pawn towards the direction of the cached destination */
	void MovePawnTowardsDestination(APawn* ControlledPawn);
	/** Move the given pawn directly to the cached destination using pathfinding */
	void MovePawnToDestination(APawn* ControlledPawn);
	
	/** Input handlers */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void OnDirectionalMoveTriggered(const FInputActionValue& Value);
	void OnDirectionalMoveReleased();
	
};
