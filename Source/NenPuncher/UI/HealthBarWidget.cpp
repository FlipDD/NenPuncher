// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass
	if (SpeechText)
	{
		FString s = "Enemy";
		SpeechText->SetText(FText::FromString(s));
	}

	if (HealthBar)
		HealthBar->SetPercent(1);
}

void UHealthBarWidget::UpdateHealthBar(int CurrentHealthPoints, int MaxHealthPoints)
{
	// Progress bar goes from 0 to 1
	float Percent = (float) CurrentHealthPoints / (float) MaxHealthPoints;
	if (HealthBar)
		HealthBar->SetPercent(Percent);
}
