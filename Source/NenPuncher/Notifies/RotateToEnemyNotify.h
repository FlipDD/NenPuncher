// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RotateToEnemyNotify.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API URotateToEnemyNotify : public UAnimNotify
{
	GENERATED_BODY()

	URotateToEnemyNotify();
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY()
		class UTimelineComponent* MyTimeline;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* FloatCurve;

	UPROPERTY(EditAnywhere)
		float InterpSpeed;

	UFUNCTION()
		void TimelineCallback(float val);

	void PlayTimeline();

	UPROPERTY()
		AActor* ClosestEnemy;
	UPROPERTY()
		class ANenPuncherCharacter* Player;
};
