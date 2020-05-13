// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "MyProject4.h"
#include "FPSProjectile.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameHud.h"

using namespace std;
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight - 50.0f));

	FPSCameraComponent->bUsePawnControlRotation = true;

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Braco")));

	HandMesh->SetupAttachment(FPSCameraComponent);

	pontuacao = 0;

}

vector<string> a;
AGameHud* MeuHud;
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	string stra;
	ifstream arquivo("C:/Users/GODZILLA/Documents/Unreal Projects/MyProject4/Source/MyProject4/objects.txt");

	while (getline(arquivo, stra))
	{
		a.push_back(stra);
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(a.begin(), a.end(), std::default_random_engine(seed));
	ULocalPlayer* teste = GetWorld()->GetFirstLocalPlayerFromController();
	FLocalPlayerContext teste2 = FLocalPlayerContext(teste);

	MeuHud = Cast<AGameHud>(teste2.GetHUD());
	MeuHud->UpdateSentence(a[0].c_str());
	arquivo.close();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int range = 500;
	int radius = 5;
	FVector cameraLocation = FPSCameraComponent->GetComponentLocation();
	FVector forwardVector = FPSCameraComponent->GetForwardVector();
	FVector End = cameraLocation + (forwardVector * range);
	FCollisionShape collShape = FCollisionShape::MakeSphere(radius);
	FHitResult hitObject;

	TEnumAsByte<EObjectTypeQuery> ObjectToTrace = EObjectTypeQuery::ObjectTypeQuery8;
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectsToTraceAsByte;
	ObjectsToTraceAsByte.Add(ObjectToTrace);

	bool isHit = GetWorld()->SweepSingleByObjectType(hitObject, cameraLocation, End, FQuat::Identity, FCollisionObjectQueryParams(ObjectsToTraceAsByte) , collShape);
	if (isHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "1");
	}
}

void AMyCharacter::StartTracing(AActor oldActor, AActor newActor)
{
	
	TArray<UActorComponent*> Retorno = newActor.GetComponentsByTag(UPrimitiveComponent::StaticClass(), FName("outline"));
	
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveLeft", this, &AMyCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("Virar", this, &AMyCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("OlharCima", this, &AMyCharacter::InverterMouse);

	PlayerInputComponent->BindAction("Pular", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Pular", IE_Released, this, &AMyCharacter::StopJump);

	PlayerInputComponent->BindAction("Atirar", IE_Pressed, this, &AMyCharacter::Shoot);

	PlayerInputComponent->BindAction("Laser", IE_Pressed, this, &AMyCharacter::LaserBeam);

}

void AMyCharacter::MoveForward(float value)
{
	FVector direcao = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	AddMovementInput(direcao, value);
}

void AMyCharacter::MoveLeft(float value)
{
	FVector direcao = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(direcao, value);
}

void AMyCharacter::InverterMouse(float value)
{
	AddControllerPitchInput(-value);
}

void AMyCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyCharacter::StopJump()
{
	bPressedJump = false;
}

void AMyCharacter::Shoot()
{
	if (ProjectileClass) 
	{
		//Pegamos a camera

		FVector CameraLocation;

		FRotator CameraRotation;

		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;

			SpawnParams.Owner = this;

			SpawnParams.Instigator = GetInstigator();
			
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();

				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AMyCharacter::LaserBeam()
{
	FHitResult OutHit;

	FVector Start = HandMesh->GetComponentLocation(); //Pegamos o ponto da câmera
	FVector Frente = FPSCameraComponent->GetForwardVector();
	FVector End = (Start + (Frente * 1000.0f));

	FCollisionQueryParams ParamColisao;
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, ParamColisao);

	if (isHit)
	{
		if (OutHit.bBlockingHit)
		{
			FString resposta = *OutHit.GetActor()->GetName();
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, resposta);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, a[pontuacao].c_str());
			if (resposta == a[pontuacao].c_str())
			{
				pontuacao += 1;
				MeuHud->UpdatePointCount(pontuacao);
				MeuHud->UpdateSentence(a[pontuacao].c_str());
			}
		}
	}
}


