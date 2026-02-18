// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthUI.h"
#include "Components/ProgressBar.h" 
#include "Components/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UHealthUI::InitializeBind(UHealthComponent* HealthComponent)
{
	if (!HealthComponent)return;
	HealthComponent->OnHealthUpdate.AddDynamic(this, &UHealthUI::UpdateHealthBar);
}

void UHealthUI::UpdateHealthBar(float Percent)
{
	HealthBar->SetPercent(Percent);
}
