// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EX2_Waldemar_ZeitlerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AEX2_Waldemar_ZeitlerCharacter

AEX2_Waldemar_ZeitlerCharacter::AEX2_Waldemar_ZeitlerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

    // At the start bowing is false
    bBowStarted = false;

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEX2_Waldemar_ZeitlerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // Start bowing (exercise 2)
    PlayerInputComponent->BindAction("Bow", IE_Pressed, this, &AEX2_Waldemar_ZeitlerCharacter::Bow);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEX2_Waldemar_ZeitlerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEX2_Waldemar_ZeitlerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEX2_Waldemar_ZeitlerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEX2_Waldemar_ZeitlerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEX2_Waldemar_ZeitlerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEX2_Waldemar_ZeitlerCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AEX2_Waldemar_ZeitlerCharacter::OnResetVR);
}


void AEX2_Waldemar_ZeitlerCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEX2_Waldemar_ZeitlerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (!bBowStarted)
    {
        Jump();
    }	
}

void AEX2_Waldemar_ZeitlerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (!bBowStarted)
    {
        StopJumping();
    }	
}

void AEX2_Waldemar_ZeitlerCharacter::TurnAtRate(float Rate)
{
    if (!bBowStarted)
    {
        // calculate delta for this frame from the rate information
        AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
    }
}

void AEX2_Waldemar_ZeitlerCharacter::LookUpAtRate(float Rate)
{
    if (!bBowStarted)
    {
        // calculate delta for this frame from the rate information
        AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
    }	
}

void AEX2_Waldemar_ZeitlerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !bBowStarted)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEX2_Waldemar_ZeitlerCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) && !bBowStarted)
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

void AEX2_Waldemar_ZeitlerCharacter::Bow()
{
    bBowStarted = true;
}
