// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "Components/TextBlock.h"
#include "Points.generated.h"

UCLASS()
class MYPROJECT4_API UPoints : public UUserWidget
{
	GENERATED_BODY()
public:
	UPoints(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* txtCombo;
	
	void UpdateValor(int value);

};
