// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DerpHUD.generated.h"

class UDerpUserWidget;
/**
 * 
 */
UCLASS(Abstract)
class DERPQUEST_API ADerpHUD : public AHUD
{
	GENERATED_BODY()

public:

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:

	/** Pointer to the UI user widget */
	UPROPERTY()
	TObjectPtr<UDerpUserWidget> UIWidget;

	/** Type of UI Widget to spawn */
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UDerpUserWidget> UIWidgetClass;
	
};
