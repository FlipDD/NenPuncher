// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckHitNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "Player/NenPuncherCharacter.h"

void UCheckHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			Player->GetOverlappingEnemies(DamageAmount, IsRightHand);
		}
	}
}