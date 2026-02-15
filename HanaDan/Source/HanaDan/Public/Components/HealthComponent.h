// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCharacterStatusDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, float, LifePercent);

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// ステータスの初期化
	/// </summary>
	/// <param name="StatusData">ステータスのデータアセット</param>
	void InitializeStatus(const UCharacterStatusDataAsset* StatusData);

	// HPの更新
	UFUNCTION()
	void UpdateHelth(int32 Value);

public:
	// HP更新のデリゲート
	UPROPERTY()
	FHealthDelegate OnHealthUpdate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentHP;
};
