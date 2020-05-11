// Fill out your copyright notice in the Description page of Project Settings.


#include "Points.h"
#include "Engine.h"

UPoints::UPoints(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

}
void UPoints::NativeConstruct()
{
	Super::NativeConstruct();

}
void UPoints::UpdateValor(int value)
{
	if (txtCombo && value > 0)
	{
		txtCombo->SetText(FText::FromString(("Pontuacao: " + FString::FromInt(value))));
	}
}
