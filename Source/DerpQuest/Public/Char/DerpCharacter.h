// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/ICanPickup.h"
#include "DerpCharacter.generated.h"

class UDerpAbilitySystemComponent;
class UDerpAbility;

UCLASS()
class DERPQUEST_API ADerpCharacter : public ACharacter, public IICanPickup, public IAbilitySystemInterface 
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

	// Grant abilities on the server. The Ability Specs will be replicated to the owning client.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GiveAbility(TSubclassOf<UDerpAbility> AbilityClass, int32 InputID = -1);

	// Activate an ability by input ID
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputID);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Initialize the character's abilities
	virtual void InitializeAbilities();

	// The Ability System Component for this character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDerpAbilitySystemComponent> AbilitySystemComponent;

	// Default active abilities for this character. Will be given an input ID equal to their index in the array.
	// These will be granted on the server and replicated to the owning client.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UDerpAbility>> DefaultActiveAbilities;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


};
