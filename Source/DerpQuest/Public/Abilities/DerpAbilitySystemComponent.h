// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DerpAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class DERPQUEST_API UDerpAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UDerpAbilitySystemComponent();

	// Whether the default abilities have been given to this component
	UPROPERTY()
	bool bDefaultAbilitiesGiven = false;
	
};
