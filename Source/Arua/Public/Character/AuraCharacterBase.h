// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InterAction/CombatInterface.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"

#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;
struct FTaggedMontage;
class UDebuffNiagaraComponent;
class USkeletalMeshComponent;
UCLASS(Abstract)
class ARUA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

    virtual UAnimMontage* GetHitReactMontage_Implementation()override;
    virtual void Die(const FVector& DeathImpluse)override;
    virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
    virtual bool IsDead_Implementation()const override;
    virtual AActor* GetAvatar_Implementation()override;
    virtual TArray<FTaggedMontage> GetAttackMontages_Implementation()override;
    virtual UNiagaraSystem* GetBloodEffect_Implementation()override;
    virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)override;
    virtual int32 GetMinionCount_Implementation()override;
    virtual void IncrementMinionCount_Implementation(int32 Amount)override;
    virtual ECharacterClass GetCharacterClass_Implementation()override;
    virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
    virtual FOnDeathSignature& GetOnDeathDelegate()override;
    virtual USkeletalMeshComponent* GetWeapon_Implementation()override;
    virtual void SetIsBeingShocked_Implementation(bool bInShock)override;
    virtual bool IsBeingShocked_Implementation()const override;

    FOnASCRegistered OnASCRegistered;
    FOnDeathSignature OnDeathDelegate;

	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpluse);

    UPROPERTY(EditAnywhere,Category="Combat")
    TArray<FTaggedMontage> AttackMontages;

    UPROPERTY(ReplicatedUsing=OnRep_Stunned,BlueprintReadOnly)
    bool bIsStunned = false;

    UPROPERTY(ReplicatedUsing=OnRep_Burned,BlueprintReadOnly)
    bool bIsBurned = false;


    UPROPERTY(Replicated, BlueprintReadOnly)
    bool bIsBeingShocked = false;

    UFUNCTION()
    virtual void OnRep_Stunned();

    UFUNCTION()
    virtual void OnRep_Burned();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon;


	UPROPERTY(EditAnyWhere, Category = "Combat")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnyWhere, Category = "Combat")
	FName LeftHandSocketName;
    UPROPERTY(EditAnyWhere, Category = "Combat")
    FName RightHandSocketName;
    UPROPERTY(EditAnyWhere, Category = "Combat")
    FName TailSocketName;
    
    bool bDead = false;

    virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float BaseWalkSpeed = 600.f;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect>GameplayEffectClass,float level)const;
	virtual void InitializeDefaultAttributes()const;

	void AddCharacterAbilities();

	//Dissolve Effects
	
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Combat")
    UNiagaraSystem* BloodEffect;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    USoundBase* DeathSound;


    //Minions
    int32 MinionCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults");
    ECharacterClass CharacterClass = ECharacterClass::Warrior;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;


private:
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditAnywhere, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

};
