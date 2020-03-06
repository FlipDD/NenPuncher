// Fill out your copyright notice in the Description page of Project Settings.


#include "SetStateDefaultNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "Player/NenPuncherCharacter.h"

void USetStateDefaultNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			Player->SetStateDefault();
		}
	}
}