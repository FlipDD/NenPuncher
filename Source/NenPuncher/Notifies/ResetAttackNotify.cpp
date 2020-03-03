// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetAttackNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "NenPuncherCharacter.h"

void UResetAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr) { Player->ResetAttackCount(); }
	}
}