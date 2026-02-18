// 弾のベースクラス

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DnagoProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UProjectileDataAsset;

UCLASS()
class HANADAN_API ADnagoProjectile : public AActor
{
	GENERATED_BODY()
	
	/** Provides collision detection for the projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	/** Handles movement for the projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

protected:
	// 弾のDataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<UProjectileDataAsset> ProjectileData;


public:	
	// Sets default values for this actor's properties
	ADnagoProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
