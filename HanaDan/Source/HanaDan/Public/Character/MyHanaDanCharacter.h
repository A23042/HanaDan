// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HanaDanCharacter.h"
#include "MyHanaDanCharacter.generated.h"

class UHealthComponent;
class UCharacterStatusDataAsset;
class ADangoWeapon;

/**
 * 
 */
UCLASS()
class HANADAN_API AMyHanaDanCharacter : public AHanaDanCharacter
{
	GENERATED_BODY()

/// <summary>
/// Components
/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

/// <summary>
/// エディタで弄るプロパティ
/// </summary>
protected:
	// キャラクターのステータス
	UPROPERTY(EditDefaultsOnly, Category = "Status")
	TObjectPtr<UCharacterStatusDataAsset> CharacterStatus;

	// 射撃用入力アクション
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;
	// リロード用入力アクション
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ReloadAction;

	// テスト用で最初に持っている武器を指定しておく
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ADangoWeapon> InitialWeapon;

/// <summary>
/// Overrideする関数たち
/// </summary>
public:
	AMyHanaDanCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
/// <summary>
/// 変数たち
/// </summary>
protected:
	// 現在手に持っている武器
	UPROPERTY(Replicated)
	TObjectPtr<ADangoWeapon> CurrentWeapon = nullptr;

/// <summary>
/// 自作関数たち
/// </summary>
protected:
	// 射撃
	void FiringStart();
	void FiringStop();
	// リロード
	void Reloading();

	// 死亡処理を書く
	UFUNCTION()
	void OnCharacterDeath();

public:
	bool IsDeath()const;

	UHealthComponent* GetHealthComponent()const { return HealthComponent; }
};
