// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DerpPlayerPawn.generated.h"

class ADerpCharacter;

UCLASS()
class DERPQUEST_API ADerpPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADerpPlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Pawn")
    TObjectPtr<ADerpCharacter> TargetChar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Pawn", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float LerpSpeed = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDerpSpringArmComponent* CameraBoom;

};
