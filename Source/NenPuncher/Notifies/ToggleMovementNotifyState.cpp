// Fill out your copyright notice in the Description page of Project Settings.

#include "ToggleMovementNotifyState.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Player/NenPuncherCharacter.h"

void UToggleMovementNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			auto Controller = Cast<AController>(Player->GetController());
			if (Controller != nullptr)
			{
				Controller->SetIgnoreMoveInput(true);
			}
		}
	}
}

void  UToggleMovementNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			auto Controller = Cast<AController>(Player->GetController());
			if (Controller != nullptr)
			{
				Controller->SetIgnoreMoveInput(false);
			}
		}
	}
}


