#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class JAN24_API UTimeManager : public UObject
{
	GENERATED_BODY()
	
public:
	UTimeManager();

	UFUNCTION(BlueprintCallable)
	void PauseTime();

	UFUNCTION(BlueprintCallable)
	void ResumeTime();
	
	UFUNCTION(BlueprintCallable)
	void SetTimeScale(float NewTimeScale);

protected:
	float TimeScaleBeforePause;
};
