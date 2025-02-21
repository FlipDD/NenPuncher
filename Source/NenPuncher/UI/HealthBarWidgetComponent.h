// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	virtual void InitWidget() override;

	UHealthBarWidgetComponent();
};
