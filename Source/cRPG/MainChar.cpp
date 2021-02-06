// Fill out your copyright notice in the Description page of Project Settings.


#include "MainChar.h"

// Sets default values
AMainChar::AMainChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Don't rotate when the controller rotates. That just affect the camera */
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/* Configure character movement */
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;


	/* Create a camera boom */
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	/* Create a follow camera */
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of  of the boom and let the boom adjust to match the controller orientation 
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	/* Set the default player variables. */
	isOverlappingItem = false;
	isSprinting = false;
	hasArmor = true;

	currentLevel = 1;
	upgradePoints = 4;

	strengthValue = 1;
	dexterityValue = 1;
	intellectValue = 1;

	playerHealth = 1.00f;
	playerEnergy = 1.00f;
	playerArmor = 1.00f;

}

// Called when the game starts or when spawned
void AMainChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainChar::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainChar::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainChar::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainChar::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainChar::StopJump);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AMainChar::EquipItem);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainChar::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainChar::StopSprint);

}

void AMainChar::MoveForward(float Value)
{
	// Find out which way is "forward" and record that player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void AMainChar::MoveRight(float Value)
{
	// Find out which way is "forward" and record that player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainChar::StartJump()
{
	bPressedJump = true;
}

void AMainChar::StopJump()
{
	bPressedJump = false;
}
void AMainChar::StartSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("We are now sprinting"));
	GetCharacterMovement()->MaxWalkSpeed = 1500.0f;
}

void AMainChar::StopSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("We have stopped sprinting."));
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMainChar::EquipItem()
{
	if (isOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("We picked up an item."));
	}
}

