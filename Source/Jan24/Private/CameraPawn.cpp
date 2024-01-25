// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"

ACameraPawn::ACameraPawn()
{
 //    // Set this pawn to call Tick() every frame.
 //    PrimaryActorTick.bCanEverTick = true;
 //
 //    // Create a spring arm component
 //    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
 //    SpringArm->SetupAttachment(RootComponent);
 //    SpringArm->bDoCollisionTest = false; // Do not want to pull camera in when it collides with level
 //
 //    // Create a camera component
 //    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
 //    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CameraComponent set"));
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
/* from DefaultPawn
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Up, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::Gamepad_LeftX, 1.f));
	}

*/
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	const UInputAction* MoveForwardAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveForward"));
	const UInputAction* MoveBackwardAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveBackward"));
	const UInputAction* MoveRightAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveRight"));
	const UInputAction* MoveLeftAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveLeft"));
	
	EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveForward);
	EnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveBackward);
	EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveRight);
	EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveLeft);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Callbacks set"));
}

void ACameraPawn::MoveForward(const FInputActionValue& Value)
{
	FVector MoveDirection = GetActorForwardVector() * Value.Get<float>();
	AddMovementInput(MoveDirection);
}

void ACameraPawn::MoveBackward(const FInputActionValue& Value)
{
	FVector MoveDirection = GetActorForwardVector() * -Value.Get<float>();
	AddMovementInput(MoveDirection);
}

void ACameraPawn::MoveRight(const FInputActionValue& Value)
{
	FVector MoveDirection = GetActorRightVector() * Value.Get<float>();
	AddMovementInput(MoveDirection);
}

void ACameraPawn::MoveLeft(const FInputActionValue& Value)
{
	FVector MoveDirection = GetActorRightVector() * -Value.Get<float>();
	AddMovementInput(MoveDirection);
}
