// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ICanPickup.h"
#include "PickupBase.generated.h"

class USphereComponent;

UCLASS()
class DERPQUEST_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sphere collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> CollisionSphere;

	// Called when another actor overlaps with this one
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when a pickup is collected
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup")
	void OnPickup(const TScriptInterface<IICanPickup> &PickupInterface);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
