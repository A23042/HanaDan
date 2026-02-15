// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

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

	UFUNCTION()
	void UpdateHelth(int32 Value);

public:
	UPROPERTY(BlueprintAssignable)
	FHealthDelegate OnHealthUpdate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentHP;
};
