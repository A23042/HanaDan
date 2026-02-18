// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCharacterStatusDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, float, LifePercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HANADAN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// ステータスの初期化
	/// </summary>
	/// <param name="StatusData">ステータスのデータアセット</param>
	void InitializeStatus(const UCharacterStatusDataAsset* StatusData);

	/// <summary>
	/// ダメージを受ける処理
	/// </summary>
	/// <param name="DamageAmount">ダメージ量</param>
	UFUNCTION()
	void ApplyDamage(int32 DamageAmount);
	/// <summary>
	/// 回復処理
	/// </summary>
	/// <param name="HealAmount">回復量</param>
	UFUNCTION()
	void Heal(int32 HealAmount);

	bool IsDeath()const { return bIsDeath; }

public:
	// HP更新のデリゲート
	UPROPERTY()
	FHealthDelegate OnHealthUpdate;
	// 死亡時のデリゲート
	UPROPERTY()
	FOnDeath OnDeath;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = "OnRep_currentHP")
	int32 currentHP;
	UFUNCTION()
	void OnRep_currentHP();

	UPROPERTY(Replicated)
	bool bIsDeath = false;
};
