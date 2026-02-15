// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyHanaDanCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HanaDan.h"
#include "Components/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/CharacterStatusDataAsset.h"

AMyHanaDanCharacter::AMyHanaDanCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

void AMyHanaDanCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterStatus)
	{
		HealthComponent->InitializeStatus(CharacterStatus);
	}
}
