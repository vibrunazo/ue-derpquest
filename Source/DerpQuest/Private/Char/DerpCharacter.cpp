// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/DerpCharacter.h"

#include "Abilities/DerpAbility.h"
#include "Abilities/DerpAbilitySystemComponent.h"
#include "Abilities/DerpAttributeSet.h"
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

	// Create the Attribute Set
	AttributeSet = CreateDefaultSubobject<UDerpAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ADerpCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize the character's abilities
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		// Initialize attributes
		InitializeAttributes();
		
		// Initialize the Ability System Component if it hasn't been initialized yet
		if (!AbilitySystemComponent->bDefaultAbilitiesGiven)
		{
			InitializeAbilities();
		}
	}
	
}

void ADerpCharacter::InitializeAbilities()
{
	if (!AbilitySystemComponent || !AttributeSet) return;
	if (GetLocalRole() != ROLE_Authority) return;

	if (DefaultAttributes)
	{
		ApplyEffectToSelf(DefaultAttributes, 1.0f);
	}
	
	// Grant default abilities
	int32 InputID = 0;
	for (TSubclassOf<UDerpAbility>& Ability : DefaultActiveAbilities)
	{
		if (Ability)
		{
			GiveAbility(Ability, InputID++);
		}
	}

	// Mark that we've given the default abilities
	AbilitySystemComponent->bDefaultAbilitiesGiven = true;
}

void ADerpCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent || !AttributeSet) return;
	

}

void ADerpCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level)
{
	if (!AbilitySystemComponent || !Effect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, Level, EffectContext);
	if (NewHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
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

void ADerpCharacter::GiveAbility(TSubclassOf<UDerpAbility> AbilityClass, int32 InputID)
{
	if (!AbilitySystemComponent || !AbilityClass)
	{
		return;
	}

	// Create the ability spec
	FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
    
	// If an input ID was provided, set it
	if (InputID >= 0)
	{
		AbilitySpec.InputID = InputID;
	}
    
	// Give the ability to the character
	AbilitySystemComponent->GiveAbility(AbilitySpec);
}

void ADerpCharacter::ActivateAbility(int32 InputID)
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	// Try to activate the ability by input ID
	AbilitySystemComponent->AbilityLocalInputPressed(InputID);
}

void ADerpCharacter::ApplyPickupEffect_Implementation(TSubclassOf<UGameplayEffect> EffectToApply)
{
	IICanPickup::ApplyPickupEffect_Implementation(EffectToApply);
	ApplyEffectToSelf(EffectToApply, 1.0f);
	
}

void ADerpCharacter::CancelAbilities()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
}
