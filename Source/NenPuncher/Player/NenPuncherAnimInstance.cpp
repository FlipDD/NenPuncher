// Fill out your copyright notice in the Description page of Project Settings.


#include "NenPuncherAnimInstance.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PawnMovementComponent.h"

void UNenPuncherAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
}

void UNenPuncherAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!OwningPawn)
		return;

	bIsInAir = OwningPawn->GetMovementComponent()->IsFalling();

	Speed = OwningPawn->GetVelocity().Size();
}

