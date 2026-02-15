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
	void InitializeBind(UHealthComponent* HealthComponent);

protected:
	UFUNCTION()
	void UpdateHealthBar(float Percent);
};
