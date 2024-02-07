#include "CameraPawn.h"

ACameraPawn::ACameraPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false; // Avoid the camera adjusting its position based on collision
	SpringArm->TargetArmLength = 800.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0, 0, 100));
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
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
}

void ACameraPawn::MoveForward(const FInputActionValue& Value)
{
	float CurrentPanSpeed = SpringArm->TargetArmLength <= ZoomLevelForIncreasedPanSpeed ? ClosePanSpeed : FarPanSpeed;
	FVector MoveDirection = GetActorForwardVector() * Value.Get<float>() * CurrentPanSpeed;
	SetActorLocation(GetActorLocation() + MoveDirection, true);
}

void ACameraPawn::MoveBackward(const FInputActionValue& Value)
{
	float CurrentPanSpeed = SpringArm->TargetArmLength <= ZoomLevelForIncreasedPanSpeed ? ClosePanSpeed : FarPanSpeed;
	FVector MoveDirection = GetActorForwardVector() * -Value.Get<float>() * CurrentPanSpeed;
	SetActorLocation(GetActorLocation() + MoveDirection, true);
}

void ACameraPawn::MoveRight(const FInputActionValue& Value)
{
	float CurrentPanSpeed = SpringArm->TargetArmLength <= ZoomLevelForIncreasedPanSpeed ? ClosePanSpeed : FarPanSpeed;
	FVector MoveDirection = GetActorRightVector() * Value.Get<float>() * CurrentPanSpeed;
	SetActorLocation(GetActorLocation() + MoveDirection, true);
}

void ACameraPawn::MoveLeft(const FInputActionValue& Value)
{
	float CurrentPanSpeed = SpringArm->TargetArmLength <= ZoomLevelForIncreasedPanSpeed ? ClosePanSpeed : FarPanSpeed;
	FVector MoveDirection = GetActorRightVector() * -Value.Get<float>() * CurrentPanSpeed;
	SetActorLocation(GetActorLocation() + MoveDirection, true);
}

void ACameraPawn::Zoom(const FInputActionValue& Value)
{
	const float AxisValue = -Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("Zoom: %f"), SpringArm->TargetArmLength);
	if (AxisValue != 0.f)
	{
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + AxisValue * ZoomSpeed, MinZoom, MaxZoom);
	}
}
