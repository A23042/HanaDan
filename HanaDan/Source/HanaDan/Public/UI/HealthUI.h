// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthUI.generated.h"

class AMyHanaDanCharacter;
class UProgressBar;
class UHealthComponent;

/**
 * 
 */
UCLASS()
class HANADAN_API UHealthUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;

public:
	/// <summary>
	/// デリゲートのバインド初期化
	/// </summary>
	/// <param name="HealthComponent">バインドするHealthComopnent</param>
	void InitializeBind(UHealthComponent* HealthComponent);

protected:
	/// <summary>
	/// デリゲート発火されたときに呼び出されるHPバーの更新
	/// </summary>
	/// <param name="Percent">0～1のHP％</param>
	UFUNCTION()
	void UpdateHealthBar(float Percent);
};
