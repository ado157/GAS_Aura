// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound/*=false*/) const
{
	for (const FAuraInputAction& Action : AbilityInputAction)
	{
		if (Action.InputAction&&Action.InputTags == InputTag)
		{
			return Action.InputAction;
		}

	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s],on InputConfig [%s]"),*InputTag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
}
