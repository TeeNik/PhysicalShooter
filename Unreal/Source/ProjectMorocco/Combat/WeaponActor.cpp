// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaponActor::AWeaponActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);
	MuzzleComponent = CreateDefaultSubobject<USceneComponent>("MuzzleSceneComponent");
	MuzzleComponent->SetupAttachment(Root);
}

void AWeaponActor::FirePressed()
{
	auto* Controller = GetInstigatorController();
	auto Rotation = Controller->GetControlRotation();
	auto CameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
	
	FHitResult HitResult;
	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + Rotation.Vector() * 5000;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
	if (bHit)
	{
	}

	const FVector SpawnLocation = GetMuzzleLocation() + Rotation.RotateVector(MuzzleOffset);
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Instigator = GetInstigator();
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, SpawnLocation, Rotation, ActorSpawnParams);

	BP_FirePressed();
}

void AWeaponActor::FireReleased()
{
	BP_FireReleased();
}

FVector AWeaponActor::GetMuzzleLocation() const
{
	return MuzzleComponent->GetComponentLocation();
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}
