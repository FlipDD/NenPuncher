// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackImpulseNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/NenPuncherCharacter.h"

void UAttackImpulseNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			if (!DownwardsAttack)
				Player->GetCharacterMovement()->AddImpulse(Player->GetActorForwardVector() * ImpulseForce);
			else
				Player->GetCharacterMovement()->AddImpulse((Player->GetActorForwardVector() - Player->GetActorUpVector()) * ImpulseForce);
		}
	}
}