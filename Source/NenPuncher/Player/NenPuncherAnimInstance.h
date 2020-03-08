// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NenPuncherAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class NENPUNCHER_API UNenPuncherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTimeX) override;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsMoving;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Speed;

	APawn *OwningPawn;
};
