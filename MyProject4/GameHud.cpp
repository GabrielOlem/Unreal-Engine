// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"

AGameHud::AGameHud()
{

}

void AGameHud::BeginPlay()
{
	Super::BeginPlay();
	
	if (PointsWidgetClass)
	{
		PointWidget = CreateWidget<UPoints>(GetWorld(), PointsWidgetClass);
		if (PointWidget)
		{
			PointWidget->AddToViewport();
		}
	}
}

void AGameHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHud::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHud::UpdatePointCount(int value)
{
	if (PointWidget)
	{
		PointWidget->UpdateValor(value);
	}
}