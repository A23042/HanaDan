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
	HealthComponent->OnDeath.AddDynamic(this, &AMyHanaDanCharacter::OnCharacterDeath);
}

float AMyHanaDanCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority())return 0;
	// 将来的にダメージを受けたときにいろんな処理追加する

	HealthComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AMyHanaDanCharacter::OnCharacterDeath()
{
	UKismetSystemLibrary::PrintString(this, TEXT("死亡！"), true, true, FColor::Red, 3.0f);
	// ラグドール化させてから一定時間後に死亡処理
	// 死亡処理はGameModeに任せる
	// MyGameModeを作ってその中でPlayerが死んだ処理を書く
	// 継承したGameModeでリスポーンさせるのか観戦にさせるのか決めさせる

	// 今回はテストでとりあえずHP回復させちゃう
	HealthComponent->Heal(500);
}
