#include "TimeManager.h"
#include "Kismet/GameplayStatics.h"

UTimeManager::UTimeManager()
{
	TimeScaleBeforePause = 1.0f; // Normal time scale
}

void UTimeManager::PauseTime()
{
	TimeScaleBeforePause = UGameplayStatics::GetGlobalTimeDilation(this);
	UGameplayStatics::SetGlobalTimeDilation(this, 0.0f);
}

void UTimeManager::ResumeTime()
{
	UGameplayStatics::SetGlobalTimeDilation(this, TimeScaleBeforePause);
}

void UTimeManager::SetTimeScale(float NewTimeScale)
{
	if (NewTimeScale == 0.0f)
	{
		PauseTime();
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(this, NewTimeScale);
		TimeScaleBeforePause = NewTimeScale;
	}
}
