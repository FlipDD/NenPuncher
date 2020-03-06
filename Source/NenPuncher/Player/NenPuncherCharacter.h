// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NenPuncherCharacter.generated.h"

UENUM(BlueprintType)
enum class StateEnum : uint8
{
	Attacking UMETA(DisplayName = "Attacking"),
	Default UMETA(DisplayName = "Default")
};

UCLASS(config=Game)
class ANenPuncherCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Charging Particles */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ChargedParticlesComponent;
public:
	ANenPuncherCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Animation montages. */
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage* FirstPunchMontage;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage* SecondPunchMontage;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage* ThirdPunchMontage;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage* PunchDownMontage;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage* ChargedPunchMontage;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InitialValues, meta = (AllowPrivateAccess = "true"))
		StateEnum State = StateEnum::Default;

	/** Right click Attacks */
	void ChargePunch();
	void ReleasePunch();

	/** Fighting variables */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsComboing = false;

	AActor* GetClosestEnemy();

public:
	/** Left click Attacks */
	void Punch();
	void PlaySecondPunch();
	void PlayThirdPunch();

	void AddAttackImpulse(float ImpulseForce, bool IsGroundAttack = true);
	void SetStateDefault();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

