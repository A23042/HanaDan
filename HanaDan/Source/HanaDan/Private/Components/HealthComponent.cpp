// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Data/CharacterStatusDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"

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
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("最大体力:%d"), MaxHP), true, true, FColor::Blue, 5.0f);
}

void UHealthComponent::UpdateHelth(int32 Value)
{
	OnHealthUpdate.Broadcast(currentHP / MaxHP);
}

