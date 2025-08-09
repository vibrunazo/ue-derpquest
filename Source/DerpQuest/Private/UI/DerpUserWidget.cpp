// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DerpUserWidget.h"

#include "AbilitySystemInterface.h"
#include "Abilities/DerpAttributeSet.h"
#include "Char/DerpCharacter.h"
#include "Game/DerpPlayerController.h"

void UDerpUserWidget::GetDerpPlayerController(EValidity& Result, ADerpPlayerController*& PlayerController)
{
	PlayerController = Cast<ADerpPlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		Result = EValidity::Valid;
	}
	else
	{
		Result = EValidity::Invalid;
	}
}

void UDerpUserWidget::BindToPlayerAttributes()
{
	// Get the owning player
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	ADerpPlayerController* DerpController = Cast<ADerpPlayerController>(PC);
	if (!DerpController) return;
	// Get the controlled pawn
	if (DerpController->ControlledUnits.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UI_ManaBar: ControlledUnits array is empty. Cannot bind attributes yet."));
		return;
	}
	APawn* Pawn = DerpController->ControlledUnits[0];
	// APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;
	// Check if the pawn implements IAbilitySystemInterface
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Pawn);
	if (!ASI) return;
	// Get the ability system component
	AbilitySystemComponent = ASI->GetAbilitySystemComponent();
	if (!AbilitySystemComponent) return;

	// Now you can use the ASC to bind to attribute changes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UDerpAttributeSet::GetManaAttribute()
	).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged(Data.NewValue);
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UDerpAttributeSet::GetMaxManaAttribute()
	).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged(Data.NewValue);
		});

}

void UDerpUserWidget::BroadCastInitialValues()
{
	if (!AbilitySystemComponent) return;
	OnManaChanged(AbilitySystemComponent->GetNumericAttribute(UDerpAttributeSet::GetManaAttribute()));
	OnMaxManaChanged(AbilitySystemComponent->GetNumericAttribute(UDerpAttributeSet::GetMaxManaAttribute()));
}

