// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HanaDanCharacter.h"
#include "MyHanaDanCharacter.generated.h"

class UHealthComponent;

/**
 * 
 */
UCLASS()
class HANADAN_API AMyHanaDanCharacter : public AHanaDanCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

public:
	AMyHanaDanCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UHealthComponent* GetHealthComponent()const { return HealthComponent; }
};
