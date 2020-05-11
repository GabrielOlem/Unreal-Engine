// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "Points.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API AGameHud : public AHUD
{
	GENERATED_BODY()
public:
    AGameHud();

    virtual void DrawHUD() override;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION()
        void UpdatePointCount(int value);

    UPROPERTY(EditDefaultsOnly, Category = "widgets")
        TSubclassOf<UUserWidget> PointsWidgetClass;

private:
    UPoints* PointWidget;
};
