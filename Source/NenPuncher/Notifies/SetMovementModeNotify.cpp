// Fill out your copyright notice in the Description page of Project Settings.


#include "SetMovementModeNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/NenPuncherCharacter.h"

void USetMovementModeNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			Player->GetCharacterMovement()->SetMovementMode(MovementMode);
		}
	}
}