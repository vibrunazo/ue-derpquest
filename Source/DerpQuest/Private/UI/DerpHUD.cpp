// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DerpHUD.h"
#include "UI/DerpUserWidget.h" 


void ADerpHUD::BeginPlay()
{
	Super::BeginPlay();

	// spawn the UI widget
	UIWidget = CreateWidget<UDerpUserWidget>(GetOwningPlayerController(), UIWidgetClass);
	check(UIWidget);
	
	// add the UI widget to the screen
	UIWidget->AddToViewport(0);
}
