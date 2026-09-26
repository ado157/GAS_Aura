// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraPassiveAbility.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
// 修复开始 9/26：声明 UAbilitySystemBlueprintLibrary。
#include "AbilitySystemBlueprintLibrary.h"
// 修复结束。
void UAuraPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
    {

    }
}

void UAuraPassiveAbility::ReceiveDeactivate(const FGameplayTag& AbilityTag)
{
    if (AbilityTags.HasTagExact(AbilityTag))
    {
        EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);

    }
}
