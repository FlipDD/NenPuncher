// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayCamShakeNotify.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API UPlayCamShakeNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> CameraShaker;

	UPROPERTY(EditAnywhere)
		float InnerRadius = 500;

	UPROPERTY(EditAnywhere)
		float OutterRadius = 5000;
};
