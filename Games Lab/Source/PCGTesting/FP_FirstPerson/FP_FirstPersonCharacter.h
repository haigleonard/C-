// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "CCTVPawn.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "FP_FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;
UCLASS(config=Game)
class AFP_FirstPersonCharacter : public ACharacter, public IGenericTeamAgentInterface

{
	GENERATED_BODY()
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* FP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom2;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera2;

public:
	AFP_FirstPersonCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
		UAnimMontage* ClimbAnimation;

	/* This is when calculating the trace to determine what the weapon has hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponRange;
	
	/* This is multiplied by the direction vector when the weapon trace hits something to apply velocity to the component that is hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponDamage;

	UPROPERTY()
	float MaxUseDistance = 200;
	UPROPERTY()
	bool isNewFocus = false;
	UPROPERTY()
		bool bomb = false;
	bool ladder = false;
	bool ladderAnim = false;
	int timer = 0;
	bool choke = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float health = 0.5;
	bool ladderClim = false;
	bool CCTVBool = false;
	FVector ladderNei;
	UPROPERTY(BlueprintReadWrite)
		FVector teleportVector;

	inline void teleport(FVector tele) {
		teleportVector = tele;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool getbombDetec();
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool getLadderDetec();
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool returnClimb();
	UFUNCTION(BlueprintCallable, Category = "Action")
		FVector AILoc();
	UFUNCTION(BlueprintCallable, Category = "Action")
		FVector GetAIForwardVector();
	UFUNCTION(BlueprintCallable, Category = "Action")
		void setChoke(bool ChokeB);
	UFUNCTION(BlueprintCallable, Category = "Action")
		float circleRetX(float X, float rot);
	UFUNCTION(BlueprintCallable, Category = "Action")
		float circleRetY(float Y, float rot);
	UFUNCTION(BlueprintCallable, Category = "Action")
		FRotator AIRot();
	UFUNCTION(BlueprintCallable, Category = "Action")
		float returnHealth();
	UFUNCTION(BlueprintCallable, Category = "Action")
		void reduceHealth();
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool getladderClim();
	UFUNCTION(BlueprintCallable, Category = "Action")
	void setladNei(FVector ladnei);
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool getCCTVBool();

protected:

	/** Handler for a touch input beginning. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	virtual void Tick(float DeltaTime) override;

	/** Fires a virtual projectile. */
	void OnFire();

	void ChokeMethod();
	void CheatMethod();
	void HealthMethod();
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

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

	/* 
	 * Performs a trace between two points
	 * 
	 * @param	StartTrace	Trace starting point
	 * @param	EndTrac		Trace end point
	 * @returns FHitResult returns a struct containing trace result - who/what the trace hit etc.
	 */
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Structure that handles touch data so we can process the various stages of touch. */
	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	/*
	 * Handle begin touch event.
	 * Stores the index and location of the touch in a structure
	 *
	 * @param	FingerIndex	The touch index
	 * @param	Location	Location of the touch
	 */
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/*
	 * Handle end touch event.
	 * If there was no movement processed this will fire a projectile, otherwise this will reset pressed flag in the touch structure
	 *
	 * @param	FingerIndex	The touch index
	 * @param	Location	Location of the touch
	 */
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/*
	 * Handle touch update.
	 * This will update the look position based on the change in touching position
	 *
	 * @param	FingerIndex	The touch index
	 * @param	Location	Location of the touch
	 */
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);

	// Structure to handle touch updating
	TouchData	TouchItem;
	
	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	void TryEnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	inline static void resetPlayerStatus() {
		playerCreated = false;
	}

private:
	UPROPERTY()
	bool isPlayer = false;

	UPROPERTY()
		FGenericTeamId teamId;

	UPROPERTY()
		ACCTVPawn *currentlyHacking = nullptr;


	//UPROPERTY()
		//TSubclassOf<AStaticMeshActor> ladderBP;

	virtual FGenericTeamId GetGenericTeamId() const override;

	static bool playerCreated;
};

