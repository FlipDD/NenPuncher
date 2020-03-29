// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthPoints = MaxHealth;
}

void UHealthComponent::Heal(int Amount)
{
	HealthPoints += Amount;

	if (HealthPoints > MaxHealth)
		HealthPoints = MaxHealth;
}

void UHealthComponent::Damage(int Amount)
{
	HealthPoints -= Amount;

	// check if died after RUNNING this By calling GetHealth()
}