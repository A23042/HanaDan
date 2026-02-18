// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DnagoProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
ADnagoProjectile::ADnagoProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicateMovement(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = SphereCollision;

}

// Called when the game starts or when spawned
void ADnagoProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADnagoProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

