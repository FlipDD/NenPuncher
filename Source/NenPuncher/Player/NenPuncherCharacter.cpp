// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NenPuncherCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

#include "Enemy.h"

ANenPuncherCharacter::ANenPuncherCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ChargedParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>("ChargingPunchParticles");
	ChargedParticlesComponent->SetupAttachment(GetMesh(), FName("RightHand"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANenPuncherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ANenPuncherCharacter::Punch);

	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &ANenPuncherCharacter::ChargePunch);
	PlayerInputComponent->BindAction("RightClick", IE_Released, this, &ANenPuncherCharacter::ReleasePunch);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANenPuncherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANenPuncherCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANenPuncherCharacter::TurnAtRate);
	
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANenPuncherCharacter::LookUpAtRate);
}

//////////////////////////////////////////////////////////////////////////
// Attacks
void ANenPuncherCharacter::Punch()
{
	// Rotate to nearest + looking target here or in a notify?
	if (State == StateEnum::Default)
	{
		if (GetCharacterMovement()->IsMovingOnGround())
		{
			State = StateEnum::Attacking;
			PlayAnimMontage(FirstPunchMontage);
		}
		else if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
		{
			// REVIEW with punch down and start combo rigth away <----------------------------
			if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(PunchDownMontage))
			{
				PlayAnimMontage(PunchDownMontage);
				GetCharacterMovement()->StopMovementImmediately();
				AddActorLocalRotation(FRotator(-45, 0, 0));
			}
		}
	}
	else if (State == StateEnum::Attacking)
	{
		IsComboing = true;
	}
}

// REVIEW: Change these to take the montage as a parameter instead? <-------------------------
void ANenPuncherCharacter::PlaySecondPunch()
{
	if (IsComboing)
	{
		IsComboing = false;
		PlayAnimMontage(SecondPunchMontage);
	}
	else
	{
		SetStateDefault();
	}
}

void ANenPuncherCharacter::PlayThirdPunch()
{
	if (IsComboing)
	{
		IsComboing = false;
		PlayAnimMontage(ThirdPunchMontage);
	}
	else
	{
		SetStateDefault();
	}
}

AActor* ANenPuncherCharacter::GetClosestEnemy()
{
	auto World = GetWorld();
	if (!ensure(World != nullptr))
		return nullptr;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> OutHit;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		World,
		GetActorLocation(),
		GetActorLocation() + (GetActorForwardVector() * 30),
		300,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true);

	float Distance = MAX_FLT;
	AActor* ClosestActor = nullptr;
	for (auto hit : OutHit)
	{
		auto Actor = Cast<AActor>(hit.Actor);
		if (Actor)
		{
			FString Name = Actor->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Actor hit name is: %s"), &Name);

			auto Enemy = Cast<AEnemy>(Actor);
			if (Enemy)
			{
				float NewDistance = (GetActorLocation() - Enemy->GetActorLocation()).Size();
				if (NewDistance < Distance)
				{
					Distance = NewDistance;
					ClosestActor = ClosestActor;
				}
			}
		}
	}
	
	return ClosestActor;
}

void ANenPuncherCharacter::SetStateDefault()
{
	State = StateEnum::Default;
}

void ANenPuncherCharacter::ChargePunch()
{
	PlayAnimMontage(ChargedPunchMontage);
	ChargedParticlesComponent->Activate(true);
}

void ANenPuncherCharacter::ReleasePunch()
{
	PlayAnimMontage(ChargedPunchMontage, 1, FName("End"));
	ChargedParticlesComponent->Deactivate();
}

void ANenPuncherCharacter::AddAttackImpulse(float ImpulseForce, bool IsGroundAttack)
{
	if (IsGroundAttack)
		GetCharacterMovement()->AddImpulse(GetActorForwardVector() * ImpulseForce);
	else
		GetCharacterMovement()->AddImpulse((GetActorForwardVector() - GetActorUpVector()) * ImpulseForce);
}

//////////////////////////////////////////////////////////////////////////
// Movement
void ANenPuncherCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANenPuncherCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANenPuncherCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANenPuncherCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
