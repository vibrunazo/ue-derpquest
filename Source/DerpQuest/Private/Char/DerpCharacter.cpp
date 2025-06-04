// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/DerpCharacter.h"

// Sets default values
ADerpCharacter::ADerpCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADerpCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

