// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyBase.generated.h"

UCLASS()
class DERPQUEST_API AKeyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Speed at which the actor moves towards the target location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Movement")
	float MoveSpeed = 5.0f;

	// Target location to move towards
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Movement")
	FVector TargetLocation = FVector::ZeroVector;

	// Offset from the target location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Movement")
	FVector TargetOffset = FVector::ZeroVector;

	// Actor to follow (if set, will override TargetLocation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Movement")
	AActor* TargetActor = nullptr;

private:
	// Whether the actor should be moving towards the target location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Key Movement")
	bool bShouldMove = false;

};
