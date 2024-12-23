// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

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
}

void UWeaponComponent::FireReleased()
{
	UE_LOG(LogTemp, Log, TEXT("FireReleased"));
}
