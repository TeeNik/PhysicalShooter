// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingTargetingComponent.h"

#include "HackableActorComponent.h"

UHackingTargetingComponent::UHackingTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UHackingTargetingComponent::GetCurrentTarget() const
{
	return CurrentTarget.Get();
}

bool UHackingTargetingComponent::GetMinMaxOnScreen(FVector& Min, FVector& Max)
{
	if (CurrentTarget.IsValid())
	{
		auto Box = CurrentTarget->GetComponentsBoundingBox(true, false);
	}
	return false;
}


void UHackingTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHackingTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Forward = GetOwner()->GetInstigatorController()->GetControlRotation().Vector();

	CurrentTarget.Reset();
	
	FHitResult Hit;
	const FVector Start = GetOwner()->GetActorLocation();
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Forward * 2000, ECC_Visibility))
	{
		auto* Actor = Hit.GetActor();
		if (IsValid(Actor) && Actor->FindComponentByClass<UHackableActorComponent>() != nullptr)
		{
			CurrentTarget = Actor;
		}
	}
}

