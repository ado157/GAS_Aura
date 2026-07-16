// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

//属性信息结构体
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag=FGameplayTag();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName=FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue=0.0f;

};


/**
 * 
 */
UCLASS()
class ARUA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag,bool bLogNotFound=false) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
};
