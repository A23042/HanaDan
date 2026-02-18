// 弾の設定項目用のデータアセット

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class HANADAN_API UProjectileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	// 基礎ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Damage = 50;

	// 弾速
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ProjectileSpeed = 4000.0f;

	// 跳弾回数
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BounceCount = 0;

	// 着弾時の効果(速度低下、爆発等)
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TObjectPtr<UDangoEffect> DangoEffect;
};
