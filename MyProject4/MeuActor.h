// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinhaInterface.h"
#include "MeuActor.generated.h"

UCLASS()
class MYPROJECT4_API AMeuActor : public AActor, public IMinhaInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeuActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
