// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

public:
	void UpdateHealthBar(int CurrentHealthPoints, int MaxHealthPoints);
};
