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
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 TimeRemaining;
	
protected:
	virtual void BeginPlay() override;

private:
	// Total time in seconds
	UPROPERTY(EditAnywhere, Category = "Game")
	int32 TotalTime = 60; // Default to 60 seconds


	FTimerHandle TimerHandle;

	// Update the timer
	void UpdateTimer();
};
