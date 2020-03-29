// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NENPUNCHER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Max value of health
	UPROPERTY(EditAnywhere, Category = HP)
		int MaxHealth = 100;

	// Current value for health
	UPROPERTY(VisibleAnywhere, Category = HP)
		int HealthPoints;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Health system functions
	void Heal(int Amount);
	void Damage(int Amount);

	/** Returns current health points **/
	FORCEINLINE int GetHealthPoints() const { return HealthPoints; }
};
