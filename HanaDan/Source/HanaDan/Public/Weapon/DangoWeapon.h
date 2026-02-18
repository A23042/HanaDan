// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DangoWeapon.generated.h"

class UWeaponDataAsset;

UCLASS()
class HANADAN_API ADangoWeapon : public AActor
{
	GENERATED_BODY()
	
	/** Provides collision detection for the projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SkewersMesh;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<UWeaponDataAsset> WeaponData;

public:	
	// Sets default values for this actor's properties
	ADangoWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void Server_FiringStart();

	UFUNCTION(Server, Reliable)
	void Server_FiringStop();

	UFUNCTION(Server, Reliable)
	void Server_Reloading();
};
