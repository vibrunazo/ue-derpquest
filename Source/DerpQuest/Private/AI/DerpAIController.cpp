// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DerpAIController.h"

#include "Components/StateTreeAIComponent.h"
#include "Perception/AIPerceptionComponent.h"

ADerpAIController::ADerpAIController()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeComponent"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ADerpAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// if (StateTreeComponent)
	// {
	// 	StateTreeComponent->StartLogic();
	// }
}

