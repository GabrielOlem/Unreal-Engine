// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"

#include "HitComboWidget.h"

#include "InGameHUD.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT4_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();

	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateComboCount(int32 Value);

	UFUNCTION()
		void ResetCombo();

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> HitComboWidgetClass;

private:
	UHitComboWidget* HitComboWidget;
};