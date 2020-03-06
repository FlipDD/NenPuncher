
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayNextPunchNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "Player/NenPuncherCharacter.h"

void UPlayNextPunchNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			if (PunchNumber == 2)
			{
				Player->PlaySecondPunch();
			}
			else if (PunchNumber == 3)
			{
				Player->PlayThirdPunch();
			}
		}
	}
}
