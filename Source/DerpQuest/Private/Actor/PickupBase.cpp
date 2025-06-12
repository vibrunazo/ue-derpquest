// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PickupBase.h"

#include "Components/SphereComponent.h"
#include "Interfaces/ICanPickup.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and configure the sphere collision component
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->InitSphereRadius(50.0f);
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->SetGenerateOverlapEvents(true);
    
	// Set up the overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor implements the ICanPickup interface
	if (OtherActor && OtherActor->Implements<UICanPickup>())
	{
		// Get the interface
		TScriptInterface<IICanPickup> PickupInterface(OtherActor);
		if (PickupInterface.GetInterface() != nullptr)
		{
			// Call the OnPickup event
			OnPickup(PickupInterface);
		}
	}
}

void APickupBase::OnPickup_Implementation(const TScriptInterface<IICanPickup> &PickupInterface)
{
	// Base implementation does nothing
	// Override in child classes to implement specific pickup behavior
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

