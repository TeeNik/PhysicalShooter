// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "Kismet/GameplayStatics.h"

AWeaponActor::AWeaponActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);
	MuzzleComponent = CreateDefaultSubobject<USceneComponent>("MuzzleSceneComponent");
}

void AWeaponActor::FirePressed()
{
	auto* Controller = GetOwner()->GetInstigatorController();
	auto Rotation = Controller->GetControlRotation();
	auto CameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
	
	FHitResult HitResult;
	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + Rotation.Vector() * 5000;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
	if (bHit)
	{
	}
	DrawDebugLine(GetWorld(), TraceStart, bHit ? HitResult.Location : TraceEnd, FColor::Red, false, 10);
}

void AWeaponActor::FireReleased()
{
}

FVector AWeaponActor::GetMuzzleLocation() const
{
	return MuzzleComponent->GetComponentLocation();
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}
