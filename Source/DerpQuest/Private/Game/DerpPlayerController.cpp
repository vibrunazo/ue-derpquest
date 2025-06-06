// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DerpPlayerController.h"

#include "DerpQuestPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ADerpPlayerController::ADerpPlayerController()
{
	bIsTouch = false;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ADerpPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADerpPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADerpPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADerpPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADerpPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ADerpPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ADerpPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ADerpPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ADerpPlayerController::OnTouchReleased);

		// Setup directional move input events
		EnhancedInputComponent->BindAction(DirectionalMoveAction, ETriggerEvent::Started, this, &ADerpPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(DirectionalMoveAction, ETriggerEvent::Triggered, this, &ADerpPlayerController::OnDirectionalMoveTriggered);
		EnhancedInputComponent->BindAction(DirectionalMoveAction, ETriggerEvent::Completed, this, &ADerpPlayerController::OnDirectionalMoveReleased);
		EnhancedInputComponent->BindAction(DirectionalMoveAction, ETriggerEvent::Canceled, this, &ADerpPlayerController::OnDirectionalMoveReleased);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADerpPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADerpPlayerController::OnInputStarted()
{
	StopMovement();
}

void ADerpPlayerController::OnSetDestinationTriggered()
{
	if (bIsDirectionalMovementActive) return;
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADerpPlayerController::OnSetDestinationReleased()
{
	if (bIsDirectionalMovementActive) return;
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void ADerpPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADerpPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ADerpPlayerController::OnDirectionalMoveTriggered(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	bIsDirectionalMovementActive = !MovementVector.IsNearlyZero();
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		// Fixed world directions
		const FVector ForwardDirection = FVector::ForwardVector;  // World X axis (forward)
		const FVector RightDirection = FVector::RightVector;      // World Y axis (right)

		// Calculate movement direction based on input
		FVector MovementDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
		MovementDirection.Normalize();
		
		ControlledPawn->AddMovementInput(MovementDirection, 1.0, false);
	}
}

void ADerpPlayerController::OnDirectionalMoveReleased()
{
	bIsDirectionalMovementActive = false;
	FollowTime = 0.f;
}
