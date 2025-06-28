// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/ICanPickup.h"
#include "Interfaces/IGetHit.h"
#include "DerpCharacter.generated.h"

class UDerpAttributeSet;
class UDerpAbilitySystemComponent;
class UDerpAbility;

UCLASS()
class DERPQUEST_API ADerpCharacter : public ACharacter, public IICanPickup, public IAbilitySystemInterface, public IIGetHit
{
	GENERATED_BODY()

public:
	ADerpCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface

	// Get the Attribute Set
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	UDerpAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// Grant abilities on the server. The Ability Specs will be replicated to the owning client.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GiveAbility(TSubclassOf<UDerpAbility> AbilityClass, int32 InputID = -1);

	// Activate an ability by input ID
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputID);

	virtual void ApplyPickupEffect_Implementation(TSubclassOf<UGameplayEffect> EffectToApply) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Initialize the character's abilities
	virtual void InitializeAbilities();

	// The Ability System Component for this character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDerpAbilitySystemComponent> AbilitySystemComponent;

	// The Attribute Set for this character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDerpAttributeSet> AttributeSet;

	// Default active abilities for this character. Will be given an input ID equal to their index in the array.
	// These will be granted on the server and replicated to the owning client.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UDerpAbility>> DefaultActiveAbilities;

	// Initialize the character's attributes
	virtual void InitializeAttributes();

	// Gameplay Effect to apply on startup to set initial attribute values
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// Apply a gameplay effect to self
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level = 1.0f);


public:
	// Cancel all active abilities
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CancelAbilities();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


};
