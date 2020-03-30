// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"


UHealthComponent::UHealthComponent()
{
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthWidget->SetTwoSided(true);
	HealthWidget->SetTickWhenOffscreen(true);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthPoints = MaxHealth;

	HealthWidget->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HealthWidget->SetWidgetClass(HealthBarClass);
	HealthWidget->SetWorldScale3D(FVector(.2f));
	HealthWidget->SetRelativeLocation(FVector(0, 0, 100));
}

void UHealthComponent::Heal(int Amount)
{
	// Increase HP
	HealthPoints += Amount;

	// Make sure that HP isn't more than Max HP
	if (HealthPoints > MaxHealth)
		HealthPoints = MaxHealth;

	UpdateHealthWidget();
}

void UHealthComponent::Damage(int Amount)
{
	// Decrease HP
	HealthPoints -= Amount;

	UpdateHealthWidget();
}

void UHealthComponent::UpdateHealthWidget()
{
	// Update "UProgressBar" widget
	auto HealthBarWidget = Cast<UHealthBarWidget>(HealthWidget->GetUserWidgetObject());
	if (HealthBarWidget)
		HealthBarWidget->UpdateHealthBar(HealthPoints, MaxHealth);
}

