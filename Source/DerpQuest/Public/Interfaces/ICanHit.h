// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICanHit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UICanHit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DERPQUEST_API IICanHit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Gets the damage amount from the hitter
	 * @return The amount of damage to apply
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	float GetDamage() const;

	/**
	 * Gets the actor that is the source/caster of this hit
	 * @return The actor that is using this ability
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	AActor* GetCaster() const;
};
