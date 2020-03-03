// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayCamShakeNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
	
void UPlayCamShakeNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		if (GetWorld())
			UGameplayStatics::PlayWorldCameraShake(
				GetWorld(),
				CameraShaker,
				MeshComp->GetOwner()->GetActorLocation(),
				InnerRadius,
				OutterRadius);
	}
}

