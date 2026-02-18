// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyHanaDanCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HanaDan.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// MyLibrary
#include "Components/HealthComponent.h"
#include "Data/CharacterStatusDataAsset.h"
#include "Weapon/DangoWeapon.h"

AMyHanaDanCharacter::AMyHanaDanCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	HealthComponent->SetIsReplicated(true);
}

void AMyHanaDanCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterStatus)
	{
		HealthComponent->InitializeStatus(CharacterStatus);
	}
	HealthComponent->OnDeath.AddDynamic(this, &AMyHanaDanCharacter::OnCharacterDeath);

	if (HasAuthority())
	{
		if (InitialWeapon)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

			CurrentWeapon = GetWorld()->SpawnActor<ADangoWeapon>(InitialWeapon, GetActorTransform(), SpawnParams);
		}
	}
}

void AMyHanaDanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 発射
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AMyHanaDanCharacter::FiringStart);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AMyHanaDanCharacter::FiringStop);

		// リロード
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AMyHanaDanCharacter::Reloading);
	}
}

void AMyHanaDanCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyHanaDanCharacter, CurrentWeapon);
}

float AMyHanaDanCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority())return 0;
	// 将来的にダメージを受けたときにいろんな処理追加する

	HealthComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AMyHanaDanCharacter::FiringStart()
{
	if (CurrentWeapon && !IsDeath())
	{
		CurrentWeapon->Server_FiringStart();
	}
}

void AMyHanaDanCharacter::FiringStop()
{
	if (CurrentWeapon && !IsDeath())
	{
		CurrentWeapon->Server_FiringStop();
	}
}

void AMyHanaDanCharacter::Reloading()
{
	if (CurrentWeapon && !IsDeath())
	{
		CurrentWeapon->Server_Reloading();
	}
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

bool AMyHanaDanCharacter::IsDeath() const
{
	if (HealthComponent)
	{
		return HealthComponent->IsDeath();
	}
	return false;
}
