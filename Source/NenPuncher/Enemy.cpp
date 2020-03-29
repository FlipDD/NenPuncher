// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Components/Widget.h"

#include "HealthComponent.h"
#include "UI/HealthBarWidget.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	/*HealthWidget = CreateDefaultSubobject<UWidget>("HealthBar");
	HealthWidget->AddToRoot();*/
	//HealthWidget->SetClass(TSubclassOf<UHealthBarWidget>());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

