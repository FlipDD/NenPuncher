// Fill out your copyright notice in the Description page of Project Settings.


#include "DownwardPunchRecoverNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/NenPuncherCharacter.h"


void UDownwardPunchRecoverNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		auto Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		{
			UE_LOG(LogTemp, Warning, TEXT("Started downward notif"));

			auto Actor = Player->GetClosestEnemy();
			if (Actor == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Couldn't find the actor"));
				return;
			}

			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(
				Player->GetActorLocation(),
				Actor->GetActorLocation());

			Player->SetActorRotation(LookRotation);

			UE_LOG(LogTemp, Warning, TEXT("Completed the rotation"));
		}
	}
}