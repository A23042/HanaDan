// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Data/CharacterStatusDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	currentHP = MaxHP;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	OnHealthUpdate.Broadcast(1.0f);
	
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, currentHP);
	DOREPLIFETIME(UHealthComponent, bIsDeath);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::InitializeStatus(const UCharacterStatusDataAsset* StatusData)
{
	if (!StatusData)return;
	// 最大体力の設定
	MaxHP = StatusData->MaxHP;
	currentHP = MaxHP;
}

void UHealthComponent::ApplyDamage(int32 DamageAount)
{
	if (!GetOwner()->HasAuthority()) return;
	currentHP = FMath::Clamp(currentHP - DamageAount, 0, MaxHP);
	if (currentHP <= 0)
	{
		OnDeath.Broadcast();
	}
	OnRep_currentHP();
}

void UHealthComponent::Heal(int32 HealAmount)
{
	if (!GetOwner()->HasAuthority()) return;
	currentHP = FMath::Clamp(currentHP + HealAmount, 0, MaxHP);
	OnRep_currentHP();
}

void UHealthComponent::OnRep_currentHP()
{
	OnHealthUpdate.Broadcast((float)currentHP / (float)MaxHP);
}

