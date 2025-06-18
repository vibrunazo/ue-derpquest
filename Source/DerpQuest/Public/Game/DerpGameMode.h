// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DerpGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DERPQUEST_API ADerpGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADerpGameMode();

	// Called when the timer updates
	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
	void OnTimerUpdate(int32 NewTime);
	
	// Current time remaining
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	int32 TimeRemaining;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	int32 TimerDuration = 60; // Default to 60 seconds
	
protected:
	virtual void BeginPlay() override;

private:
	// Total time in seconds


	FTimerHandle TimerHandle;

	// Update the timer
	void UpdateTimer();
};
