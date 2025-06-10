// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/DerpCharacter.h"

#include "Abilities/DerpAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADerpCharacter::ADerpCharacter()
{
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create the camera boom component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create the camera component
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	// Create AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UDerpAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
    
	// Set replication mode for the AbilitySystemComponent
	// Mixed mode means only minimal gameplay effects are replicated to everyone, full gameplay effects only to the owner
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADerpCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize the character's abilities
	if (AbilitySystemComponent)
	{
		// Initialize the Ability System Component if it hasn't been initialized yet
		if (!AbilitySystemComponent->bDefaultAbilitiesGiven)
		{
			InitializeAbilities();
		}
	}
	
}

void ADerpCharacter::InitializeAbilities()
{
	
}

// Called every frame
void ADerpCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADerpCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ADerpCharacter::GetAbilitySystemComponent() const
{
	return Cast<UDerpAbilitySystemComponent>(AbilitySystemComponent);
}

void ADerpCharacter::GiveAbility(TSubclassOf<UDerpGameplayAbility> AbilityClass, int32 InputID)
{
}

void ADerpCharacter::ActivateAbility(int32 InputID)
{
}

