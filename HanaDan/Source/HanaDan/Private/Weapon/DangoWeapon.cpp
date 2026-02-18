// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DangoWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ADangoWeapon::ADangoWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	SkewersMesh = CreateDefaultSubobject<UStaticMeshComponent>("SkewersMesh");
	RootComponent = SkewersMesh;

}

// Called when the game starts or when spawned
void ADangoWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADangoWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADangoWeapon::Server_FiringStart_Implementation()
{
	UKismetSystemLibrary::PrintString(this, TEXT("発射！"), true, true, FColor::Blue, 1.0f);
}

void ADangoWeapon::Server_FiringStop_Implementation()
{
	UKismetSystemLibrary::PrintString(this, TEXT("射撃終わり！"), true, true, FColor::Red, 1.0f);
}

void ADangoWeapon::Server_Reloading_Implementation()
{
	UKismetSystemLibrary::PrintString(this, TEXT("リロード"), true, true, FColor::Cyan, 1.0f);
}

