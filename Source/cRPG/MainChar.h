// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainChar.generated.h"

UCLASS()
class CRPG_API AMainChar : public ACharacter
{
	GENERATED_BODY()

private:
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/* Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AMainChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isSprinting;

	// determines if the character has armor.
	bool hasArmor;

	// Allows the character to equip an item are close to.
	UFUNCTION()
		void EquipItem();

	// A functiojn to test taking damage.

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void StartSprint();

	UFUNCTION()
		void StopSprint();

	// Determines if the character is overlapping an equippable item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		bool isOverlappingItem;

	// Character's current level.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int currentLevel;

	// Amount of available upgrade points.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int upgradePoints;

	// Amount of strength that character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int strengthValue;

	// Amount of dexterity that character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int dexterityValue;

	// Amount of intellect that character currentyl has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int intellectValue;

	// Amount of health that character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int playerHealth;

	// Amount of energy that character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int playerEnergy;

	// Amount of armor that character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int playerArmor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
