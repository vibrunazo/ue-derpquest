// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "LevelAssetUserData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DERPQUEST_API ULevelAssetUserData : public UAssetUserData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 TimerDuration = 60;
	
};
