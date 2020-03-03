// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackImpulseNotify.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API UAttackImpulseNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	UPROPERTY(EditAnywhere)
		float ImpulseForce = 5000;
	UPROPERTY(EditAnywhere)
		bool DownwardsAttack = false;
};
