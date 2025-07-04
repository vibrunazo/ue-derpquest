// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DerpAIController.generated.h"

class UStateTreeAIComponent;
/**
 * 
 */
UCLASS()
class DERPQUEST_API ADerpAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADerpAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;
};
