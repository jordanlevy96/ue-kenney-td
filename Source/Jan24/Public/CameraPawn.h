#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h" 
#include "CameraPawn.generated.h"

UCLASS()
class JAN24_API ACameraPawn : public ASpectatorPawn
{
    GENERATED_BODY()

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(const FInputActionValue& Value);
	virtual void MoveBackward(const FInputActionValue& Value);
	virtual void MoveRight(const FInputActionValue& Value);
	virtual void MoveLeft(const FInputActionValue& Value);

	void Zoom(const FInputActionValue& Value);

	
public:
    ACameraPawn();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinZoom = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxZoom = 3200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float FarPanSpeed = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float ClosePanSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float ZoomLevelForIncreasedPanSpeed = 1600.0f; 
};
