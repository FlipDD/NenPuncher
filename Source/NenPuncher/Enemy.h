// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class NENPUNCHER_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	/** Health component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UHealthComponent* HealthComponent;

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns HealthComponent subobject */
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
};
