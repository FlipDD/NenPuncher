// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DownwardPunchRecoverNotify.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API UDownwardPunchRecoverNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
