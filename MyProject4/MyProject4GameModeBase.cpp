// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject4.h"
#include "MyProject4GameModeBase.h"

void AMyProject4GameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine) 
	{
		//Mostra uma mensagem de debug por 5s
		//O valor -1 indica que não precisaremos atualizar essa mensagem
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello world, this is gme"));
	}
}
