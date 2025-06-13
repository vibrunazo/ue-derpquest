// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DerpAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDerpAttributeSet::UDerpAttributeSet()
{
	// Initialize attributes to default values
	Health = 100.0f;
	MaxHealth = 100.0f;
	Mana = 100.0f;
	MaxMana = 100.0f;
}

void UDerpAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register attributes for replication
	DOREPLIFETIME_CONDITION_NOTIFY(UDerpAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDerpAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDerpAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDerpAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UDerpAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDerpAttributeSet, Health, OldHealth);
}

void UDerpAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDerpAttributeSet, MaxHealth, OldMaxHealth);
}

void UDerpAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDerpAttributeSet, Mana, OldMana);
}

void UDerpAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDerpAttributeSet, MaxMana, OldMaxMana);
}
