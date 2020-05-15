// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateToEnemyNotifyState.h"

#include "Components/SkeletalMeshComponent.h"
#include "Player/NenPuncherCharacter.h"

#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"

URotateToEnemyNotifyState::URotateToEnemyNotifyState()
{
	//if (FloatCurve != NULL)
	//{
	//	FOnTimelineFloat onTimelineCallback;

	//	MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
	//	MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts

	//	MyTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
	//	MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

	//	MyTimeline->SetLooping(true);
	//	MyTimeline->SetTimelineLength(2.0f);
	//	MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	//	MyTimeline->SetPlaybackPosition(0.0f, false);

	//	//Add the float curve to the timeline and connect it to your timelines's interpolation function
	//	onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
	//	MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
	//	MyTimeline->RegisterComponent();
	//}
}

void URotateToEnemyNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp->GetOwner() != nullptr)
	{
		Player = Cast<ANenPuncherCharacter>(MeshComp->GetOwner());
		if (Player != nullptr)
		{
			ClosestEnemy = nullptr;
			ClosestEnemy = Player->GetClosestEnemy();
			if (ClosestEnemy)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found an enemy"));
				//MyTimeline->PlayFromStart();
			}
		}
	}
}

void URotateToEnemyNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (ClosestEnemy)
	{
		float CurrentYaw = Player->GetActorRotation().Yaw;
		FVector ThisLocation = Player->GetActorLocation();
		FVector TargetLocation = ClosestEnemy->GetActorLocation();
		FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(ThisLocation, TargetLocation);
		FRotator InterpedRotation = FMath::RInterpTo(Player->GetActorRotation(), DesiredRotation, FrameDeltaTime, InterpSpeed);
		FRotator NewRotation = FRotator(0, InterpedRotation.Yaw, 0);

		Player->SetActorRotation(NewRotation);

		UE_LOG(LogTemp, Warning, TEXT("Playing timeline"));
	}
}
