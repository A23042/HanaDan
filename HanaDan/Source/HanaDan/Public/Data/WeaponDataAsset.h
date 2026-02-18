// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

class UProjectileDataAsset;

/**
 * 
 */
UCLASS(BlueprintType)
class HANADAN_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	// 発射レート
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRate = 0.8f;

	// リロード時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ReloadTime = 1.5f;

	// 団子の数
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MagazinSize = 3;

	// マガジン内の団子構成
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UProjectileDataAsset>> MagazinProjectiles;
};
