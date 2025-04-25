// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponSpotComponent.h"
#include "ProjectMorocco/Combat/WeaponActor.h"

UWeaponComponent::UWeaponComponent()
{
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(WeaponActorClass, TEXT("WeaponActorClass is empty")))
	{
		if (UWeaponSpotComponent* WeaponSpot = GetOwner()->FindComponentByClass<UWeaponSpotComponent>())
		{
			FTransform SpotTransform = WeaponSpot->GetComponentTransform();
			WeaponActor = Cast<AWeaponActor>(GetWorld()->SpawnActor(WeaponActorClass, &SpotTransform));
			WeaponActor->AttachToComponent(WeaponSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			WeaponActor->SetInstigator(Cast<APawn>(GetOwner()));
		}
	}
}

void UWeaponComponent::FirePressed()
{
	if (WeaponActor)
	{
		WeaponActor->FirePressed();
	}
}

void UWeaponComponent::FireReleased()
{
	if (WeaponActor)
	{
		WeaponActor->FireReleased();
	}
}

