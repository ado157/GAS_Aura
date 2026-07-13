// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "InterAction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ARUA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
	
public:
		AAuraEnemy();
		//EnemyInterface
		virtual void HighlightActor() override;
		virtual void UnHighlightActor() override;

		//CombatInterface
		virtual int32 GetPlayerLevel() override;


protected:
	virtual void BeginPlay()override;

	virtual void InitAbilityActorInfo()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults");
	int32 Level = 1;
};
