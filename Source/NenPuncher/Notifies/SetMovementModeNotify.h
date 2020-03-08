// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Engine/EngineTypes.h"
#include "SetMovementModeNotify.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API USetMovementModeNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EMovementMode> MovementMode;
};
