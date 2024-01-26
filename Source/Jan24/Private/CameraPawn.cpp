#include "CameraPawn.h"

ACameraPawn::ACameraPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent); // Attach to the root component
	SpringArm->bDoCollisionTest = false; // Avoid the camera adjusting its position based on collision
	SpringArm->TargetArmLength = 800.f; // Starting length of the spring arm (adjust as needed)
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f)); // Adjust to the desired angle for RTS

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach to the spring arm
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	const UInputAction* MoveForwardAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveForward"));
	const UInputAction* MoveBackwardAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveBackward"));
	const UInputAction* MoveRightAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveRight"));
	const UInputAction* MoveLeftAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_MoveLeft"));

	const UInputAction* ZoomAction = FindObject<UInputAction>(ANY_PACKAGE, TEXT("IA_Zoom"));
	
	EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveForward);
	EnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveBackward);
	EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveRight);
	EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ACameraPawn::MoveLeft);

	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACameraPawn::Zoom);

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

void ACameraPawn::Zoom(const FInputActionValue& Value)
{
	const float AxisValue = -Value.Get<float>();	
	if (AxisValue != 0.f)
	{
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + AxisValue * ZoomSpeed, MinZoom, MaxZoom);
	}
}
