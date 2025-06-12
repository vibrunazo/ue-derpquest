// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGetHit.generated.h"

class IICanHit;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UIGetHit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DERPQUEST_API IIGetHit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void GetHit(const TScriptInterface<IICanHit>& Hitter);
};
