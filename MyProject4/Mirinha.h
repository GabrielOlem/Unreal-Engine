// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Mirinha.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API UMirinha : public UUserWidget
{
	GENERATED_BODY()

public:
	UMirinha(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* txtEscolha;

	void UpdateFrase(FString value);

};
