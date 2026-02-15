// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterStatusDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class HANADAN_API UCharacterStatusDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	// 最大体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHP = 100;
};
