// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API AMyProject4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override; //Permite que StartPlay seja rodada para que possamos printar uma mensagem

};


