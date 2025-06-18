// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DerpGameMode.h"

#include "Game/Data/LevelAssetUserData.h"

ADerpGameMode::ADerpGameMode()
{
}

void ADerpGameMode::BeginPlay()
{
	Super::BeginPlay();
	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings();
	if (WorldSettings)
	{
		if (const ULevelAssetUserData* TimerData = WorldSettings->GetAssetUserData<ULevelAssetUserData>())
		{
			TimerDuration = TimerData->TimerDuration;
		}
	}

	TimeRemaining = TimerDuration;
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADerpGameMode::UpdateTimer, 1.0f, true);
}

void ADerpGameMode::UpdateTimer()
{
	if (TimeRemaining > 0)
	{
		TimeRemaining--;
		OnTimerUpdate(TimeRemaining);
	}
	else
	{
		// Timer reached zero, restart level
		GetWorldTimerManager().ClearTimer(TimerHandle);
		// UE_LOG(LogTemp, Warning, TEXT("Time's up!"));
		// Uncomment to restart level when time runs out
		// UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
	}
}
