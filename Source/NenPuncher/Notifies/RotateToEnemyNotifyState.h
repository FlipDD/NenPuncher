// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RotateToEnemyNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class NENPUNCHER_API URotateToEnemyNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	URotateToEnemyNotifyState();

private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

public:
	UPROPERTY()
		class UTimelineComponent* MyTimeline;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* FloatCurve;

	UPROPERTY(EditAnywhere)
		float InterpSpeed;

	//UFUNCTION()
	//	void TimelineCallback(float val);

	//void PlayTimeline();

	UPROPERTY()
		AActor* ClosestEnemy;
	UPROPERTY()
		class ANenPuncherCharacter* Player;
};
