// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirinha.h"
#include "Engine.h"

UMirinha::UMirinha(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMirinha::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMirinha::UpdateFrase(FString frase)
{
	if (txtEscolha)
	{
		txtEscolha->SetText(FText::FromString(frase));
	}
}