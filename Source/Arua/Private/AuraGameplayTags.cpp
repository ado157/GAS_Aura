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
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
	);
	GameplayTags.InputTag_RMB= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
	);
	GameplayTags.InputTag_1= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);
	GameplayTags.InputTag_2= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);
	GameplayTags.InputTag_3= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
	);
    GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.Passive.1"),
        FString("Input Tag Passive Ability 1")
    );
    GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.Passive.2"),
        FString("Input Tag Passive Ability 2")
    );


	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
	);


    //伤害类型

    GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage.Fire"),
        FString("Fire Damage Type")
    );
    GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage.Lightning"),
        FString("Lightning Damage Type")
    );
    GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage.Arcane"),
        FString("Arcane Damage Type")
    );
    GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage.Physical"),
        FString("Physical Damage Type")
    );

     

    //抗性类型
    GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Resistance.Arcane"),
        FString("Resistance To Arcane Damage")
    );
    GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Resistance.Fire"),
        FString("Resistance To Fire Damage")
    );
    GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Resistance.Lightning"),
        FString("Resistance To Lightning Damage")
    );
    GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Resistance.Physical"),
        FString("Resistance To Physical Damage")
    );


    //Debuff
    GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Arcane"),
        FString("Debuff for Arcane Damage")
    );
    GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Burn"),
        FString("Debuff for Fire Damage")
    );
    GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Stun"),
        FString("Debuff for Lightning Damage")
    );
    GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Physical"),
        FString("Debuff for Physical Damage")
    );

    GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Chance"),
        FString("Debuff Chance")
    );
    GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Damage"),
        FString("Debuff Damage")
    );
    GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Duration"),
        FString("Debuff Duration")
    );
    GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Debuff.Frequency"),
        FString("Debuff Frequency")
    );
    //Meta Attribute

    GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Meta.IncomingXP"),
        FString("Incoming XP Meta Attribute")
    );


    //伤害与抗性Map
    GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
    GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
    GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
    GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

    GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
    GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
    GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
    GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);

    //Effects

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag granted when Hit Reacting")
	);

    //Abilities

    GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.None"),
        FString("No Ability")
    );

    GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Attack"),
        FString("Attack Ability Tag")
    );
    GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Summon"),
        FString("Summon Ability Tag")
    );
    GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Fire.FireBolt"),
        FString("FireBolt Ability Tag")
    );
    GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Lightning.Electrocute"),
        FString("Electrocute Ability Tag")
    );

    //Passive Spells
    GameplayTags.Abilities_Passive_LifeSiphon= UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Passive.LifeSiphon"),
        FString("LifeSiphon")
    );
    GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Passive.ManaSiphon"),
        FString("ManaSiphon")
    );
    GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Passive.HaloOfProtection"),
        FString("HaloOfProtection")
    );






    GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.HitReact"),
        FString("Hit React Ability")
    );

    GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Status.Eligible"),
        FString("Eligible Status")
    );
    GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Status.Equipped"),
        FString("Equipped Status")
    );
    GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Status.Locked"),
        FString("Locked Status")
    );
    GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Status.Unlocked"),
        FString("Unlocked Status")
    );
    GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Type.None"),
        FString("Type None")
    );
    GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Type.Offensive"),
        FString("Type Offensive")
    );
    GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Type.Passive"),
        FString("Type Passive")
    );

    //Cooldown
    GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Cooldown.Fire.FireBolt"),
        FString("FireBolt Cooldown Tag")
    );

    //Combat Sockets
    GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("CombatSocket.Weapon"),
        FString("Weapon")
    );

    GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("CombatSocket.RightHand"),
        FString("Right Hand")
    );

    GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("CombatSocket.LeftHand"),
        FString("Left Hand")
    );

    GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("CombatSocket.Tail"),
        FString("Tail")
    );


    //Montage Tags
    GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Montage.Attack.1"),
        FString("Attack 1")
    );
    GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Montage.Attack.2"),
        FString("Attack 2")
    );
    GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Montage.Attack.3"),
        FString("Attack 3")
    );
    GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Montage.Attack.4"),
        FString("Attack 4")
    );

    //Player Tags
    GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Player.Block.CursorTrace"),
        FString("Block tracing under the cursor")
    );

    GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Player.Block.InputHeld"),
        FString("Block Input Held callback for Input")
    );

    GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Player.Block.InputPressed"),
        FString("Block Input Pressed callback for Input")
    );

    GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Player.Block.InputReleased"),
        FString("Block Input Released callback for Input")
    );

}

