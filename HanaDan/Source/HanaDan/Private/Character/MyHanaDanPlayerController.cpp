// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyHanaDanPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "HanaDanCameraManager.h"
#include "UI/HealthUI.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Character/MyHanaDanCharacter.h"

AMyHanaDanPlayerController::AMyHanaDanPlayerController()
{
}

void AMyHanaDanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		}
	}
}

void AMyHanaDanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void AMyHanaDanPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!HealthUIClass)return;
	if (!IsLocalController())return;

	// HPのUIを表示してバインド
	HealthUI = CreateWidget<UHealthUI>(this, HealthUIClass);
	if (HealthUI)
	{
		HealthUI->AddToViewport();
		HealthUI->InitializeBind(Cast<AMyHanaDanCharacter>(GetPawn())->GetHealthComponent());
	}
}

bool AMyHanaDanPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
