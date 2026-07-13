// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Player/AuraPlayerState.h>
#include <Player/AuraPlayerController.h>
#include <UI/HUD/AuraHUD.h>

AAuraCharacter::AAuraCharacter()
{
	// 角色朝向移动方向旋转（俯视角风格）
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	// 限制角色在水平面上移动，不允许 Z 轴偏移
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// 服务器端：Controller 分配给 Pawn 时调用
// 此时 PlayerState、ASC 均已就绪，可以安全初始化 GAS
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

// 客户端：PlayerState 同步到达时调用，保证客户端也能初始化 GAS
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}


int32 AAuraCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

// 核心：将 ASC / AttributeSet 从 PlayerState 绑定到当前角色
// PossessedBy（服务器）和 OnRep_PlayerState（客户端）都需要调用，确保双端 GAS 初始化时机正确
void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	// 告知 ASC：哪个是 Owner（PlayerState），哪个是 Avatar（当前角色）
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	// 初始化 HUD Overlay 层
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlap(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}