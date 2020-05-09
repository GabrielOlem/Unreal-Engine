// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject4.h"
#include "FPSProjectile.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight - 50.0f));

	FPSCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("To usando o player"));
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

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

	FVector Start = FPSCameraComponent->GetComponentLocation(); //Pegamos o ponto da c�mera
	FVector Frente = FPSCameraComponent->GetForwardVector();
	FVector End = (Start + (Frente * 1000.0f));

	FCollisionQueryParams ParamColisao;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, ParamColisao);

	if (isHit)
	{
		if (OutHit.bBlockingHit)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Voce atingiu: %s"), *OutHit.GetActor()->GetName()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Ponto de impacto: %s"), *OutHit.ImpactPoint.ToString()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Ponto normal de impacto: %s"), *OutHit.ImpactNormal.ToString()));
			}
		}
	}
}