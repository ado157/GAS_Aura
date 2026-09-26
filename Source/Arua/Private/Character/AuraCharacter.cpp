// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "NiagaraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Player/AuraPlayerState.h>
#include <Player/AuraPlayerController.h>
#include <UI/HUD/AuraHUD.h>
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"

#include "AuraGameplayTags.h"


AAuraCharacter::AAuraCharacter()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->bDoCollisionTest = false;

    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
    TopDownCameraComponent->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false;

    LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
    LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
    LevelUpNiagaraComponent->bAutoActivate = false;

	// 角色朝向移动方向旋转（俯视角风格）
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	// 限制角色在水平面上移动，不允许 Z 轴偏移
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

    CharacterClass = ECharacterClass::Elementalist;
}

// 服务器端：Controller 分配给 Pawn 时调用
// 此时 PlayerState、ASC 均已就绪，可以安全初始化 GAS
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

// 客户端：PlayerState 同步到达时调用，保证客户端也能初始化 GAS
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}


void AAuraCharacter::OnRep_Stunned()
{
   if (UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
   {
       const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
       FGameplayTagContainer BlockedTags;
       BlockedTags.AddTag(GameplayTags.Player_Block_CursorTrace);
       BlockedTags.AddTag(GameplayTags.Player_Block_InputHeld);
       BlockedTags.AddTag(GameplayTags.Player_Block_InputPressed);
       BlockedTags.AddTag(GameplayTags.Player_Block_InputReleased);

       if (bIsStunned)
       {
           AuraASC->AddLooseGameplayTags(BlockedTags);
           StunDebuffComponent->Activate();
       }
       else
       {
           AuraASC->RemoveLooseGameplayTags(BlockedTags);
           StunDebuffComponent->Deactivate();

       }
   }
}

void AAuraCharacter::OnRep_Burned()
{
    if (bIsBurned)
    {
        BurnDebuffComponent->Activate();
    }
    else
    {
        BurnDebuffComponent->Deactivate();

    }
}

int32 AAuraCharacter::GetSpellPoints_Implementation() const
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetSpellPoints();

}

int32 AAuraCharacter::GetAttributePoints_Implementation() const
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetAttributePoints();
}

void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->AddToSpellPoints(InSpellPoints);
}


void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->AddToAttributePoints(InAttributePoints);
}

void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->AddToLevel(InPlayerLevel);

    if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
    {
        AuraASC->UpdateAbilityStatuses(AuraPlayerState->GetPlayerLevel());
    }
}

int32 AAuraCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}

int32 AAuraCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AAuraCharacter::GetXP_Implementation() const
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetXP();
}

void AAuraCharacter::AddToXP_Implementation(int32 InXP)
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->AddToXP(InXP);
    
}


void AAuraCharacter::LevelUp_Implementation()
{
    MulticastLevelUpParticles();
}

void AAuraCharacter::MulticastLevelUpParticles_Implementation() const
{
    if (IsValid(LevelUpNiagaraComponent))
    {
        const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
        const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
        const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
        LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);

        LevelUpNiagaraComponent->Activate(true);
    }
}

int32 AAuraCharacter::GetPlayerLevel_Implementation()
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
    OnASCRegistered.Broadcast(AbilitySystemComponent);
    AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this,&AAuraCharacter::StunTagChanged);

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


