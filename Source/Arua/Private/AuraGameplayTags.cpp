// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
FAuraGameplayTags FAuraGameplayTags::GameplayTags;
void FAuraGameplayTags::InitializeNativeTags()
{

	//Primary Attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("提升物理攻击力")
	);
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("提升魔法攻击力")
	);
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("提升护甲和护甲穿透")
	);
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("提升生命力")
	);


	//Secondary Attributes

	GameplayTags.Attributes_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("减少受到的伤害，提升格挡几率")
	);
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("提升穿甲能力，提升暴击率")
	);
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("格挡几率（减少受到的50%伤害）")
	);
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("提升暴击率")
	);
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("提升暴击伤害")
	);
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("提升抗暴击能力，减少敌人暴击率")
	);
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("每秒生命恢复速度")
	);
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("每秒魔法恢复速度")
	);
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("提升最大生命值")
	);
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("提升最大魔法值")
	);

	//InputTag
	GameplayTags.InputTag_LMB= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB"),
		FString("Input Tag for Left Mouse Button")
	);
	GameplayTags.InputTag_RMB= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB"),
		FString("Input Tag for Right Mouse Button")
	);
	GameplayTags.InputTag_1= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.1"),
		FString("Input Tag for 1 key")
	);
	GameplayTags.InputTag_2= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.2"),
		FString("Input Tag for 2 key")
	);
	GameplayTags.InputTag_3= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.3"),
		FString("Input Tag for 3 key")
	);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.4"),
		FString("Input Tag for 4 key")
	);


	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
	);
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects_HitReact"),
		FString("Tag granted when Hit Reacting")
	);
}

