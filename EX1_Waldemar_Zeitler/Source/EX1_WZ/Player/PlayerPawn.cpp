// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "SpeedComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Pre set rotation speed of the pawn
    RotationRate = 15;

    // Pre set movment speed of the pawn
    MovmentSpeed = 100;

    // Set the pawn as movment component
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create a dummy root component we can attach things to.
    RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a camera and a visible object
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    // Attach our camera to our root component. Offset and rotate the camera.
    OurCamera->SetupAttachment(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-250.0f, .0f, 250.0f));
    OurCamera->SetRelativeRotation(FRotator(-45.0f, .0f, .0f));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Get the component which rises the movment and rotation speed
    SpeedComponent = Cast<USpeedComponent>(GetComponentByClass(USpeedComponent::StaticClass()));
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Button binding to call the FindActors function
    PlayerInputComponent->BindAction("ShowActors", IE_Pressed, this, &APlayerPawn::FindActors);

    // Camera view bindings
    PlayerInputComponent->BindAxis("CameraPitch", this, &APlayerPawn::AddPitchInput);
    PlayerInputComponent->BindAxis("CameraYaw", this, &APlayerPawn::AddYawInput);

    // Movment bindings
    PlayerInputComponent->BindAxis("MoveStraight", this, &APlayerPawn::AddStraightMovment);
    PlayerInputComponent->BindAxis("MoveSides", this, &APlayerPawn::AddSideMovment);   
}

void APlayerPawn::AddPitchInput(float Value)
{
    if (Value != 0.0f)
    {
        /** This is handled different to the yaw rotation, because there is a gimbald lock at around 90 and -90 degrees for the pitch.
        *   The following code solves the problem.
        */
        float RotationValue;

        // Check if the speed component should calculate the rotation rate
        if (SpeedComponent != NULL)
        {
            RotationValue = SpeedComponent->CalculateRotationRate(Value);
        }
        else
        {
            RotationValue = Value * GetWorld()->GetDeltaSeconds() * RotationRate;
        }

        FQuat QuatRotation = FQuat(FRotator(RotationValue, 0, 0));

        AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
    }
}

void APlayerPawn::AddYawInput(float Value)
{
    if (Value != 0.0f)
    {
        FRotator NewRotation = GetActorRotation();
        float Rotation;

        // Check if the speed component should calculate the rotation rate
        if (SpeedComponent != NULL)
        {
            Rotation = SpeedComponent->CalculateRotationRate(Value);
        }
        else
        {
            Rotation = Value * GetWorld()->GetDeltaSeconds() * RotationRate;
        }

        NewRotation.Yaw += Rotation;

        SetActorRotation(NewRotation);
    }
}

void APlayerPawn::AddStraightMovment(float Value)
{  
    LastLocation = GetActorLocation();

    if (Value != 0.0f)
    {
        // Calculate the speed up of the character
        float Velocity = CalculateNewVelocity(Value);

        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorForwardVector() * Velocity;

        SetActorLocation(NewLocation);
    } 
}

void APlayerPawn::AddSideMovment(float Value)
{
    if (Value != 0.0f)
    {
        // Calculate the speed up of the character
        float Velocity =  CalculateNewVelocity(Value);

        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorRightVector() * Velocity;

        SetActorLocation(NewLocation);
    }
}

float APlayerPawn::CalculateNewVelocity(float Value)
{
    float Velocity;

    // Calculate the speed, depending if a speed component was given.
    if (SpeedComponent != NULL)
    {
        Velocity = SpeedComponent->CalculateMovmentSpeed(Value);
    }
    else 
    {
        Velocity = MovmentSpeed * GetWorld()->GetDeltaSeconds() * Value;
    }

    return Velocity;
}

void APlayerPawn::FindActors()
{
    TArray<FHitResult> CloseByActors = GetActorList();

    // Print the hit results
    for (FHitResult Hit : CloseByActors)
    {
        if (Hit.Actor != nullptr)
        {
            UE_LOG(LogTemp, Log, TEXT("Found Actor: %s"), *Hit.GetActor()->GetName());
        } 
    }

    return;
}