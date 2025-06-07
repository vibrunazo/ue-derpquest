// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICanPickup.generated.h"

struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UICanPickup : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DERPQUEST_API IICanPickup
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Adds a key with the specified tag to the inventory
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory|Keys")
	void PickupKey(const FGameplayTag& KeyTag);

	// Checks if the inventory has a key with the specified tag
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory|Keys")
	bool HasKey(const FGameplayTag& KeyTag) const;
};
