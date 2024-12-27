// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::FirePressed()
{
	UE_LOG(LogTemp, Log, TEXT("FirePressed"));

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

void UWeaponComponent::FireReleased()
{
	UE_LOG(LogTemp, Log, TEXT("FireReleased"));
}

