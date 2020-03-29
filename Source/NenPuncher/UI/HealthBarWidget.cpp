// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::UpdateHealthBar(int CurrentHealthPoints, int MaxHealthPoints)
{
	// Progress bar goes from 0 to 1
	HealthBar->Percent = CurrentHealthPoints / MaxHealthPoints;
}
