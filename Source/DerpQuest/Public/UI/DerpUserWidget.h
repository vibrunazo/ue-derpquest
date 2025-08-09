// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "DerpUserWidget.generated.h"


UENUM(BlueprintType)
enum class EValidity : uint8
{
	Valid,
	Invalid
};

/**
 * 
 */
UCLASS(Abstract)
class DERPQUEST_API UDerpUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Player", meta = (ExpandEnumAsExecs = "Result"))
	void GetDerpPlayerController(EValidity& Result, ADerpPlayerController*& PlayerController);

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void BindToPlayerAttributes();
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void BroadCastInitialValues();

protected:
	
	// Callback functions for attribute changes
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnManaChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnMaxManaChanged(float NewValue);

	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;
};
