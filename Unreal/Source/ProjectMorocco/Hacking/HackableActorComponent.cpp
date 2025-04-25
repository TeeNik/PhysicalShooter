// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableActorComponent.h"
#include "Kismet/GameplayStatics.h"

UHackableActorComponent::UHackableActorComponent()
{
}

FBox2D UHackableActorComponent::GetScreenBounds() const
{
	auto Bounds = GetOwner()->GetComponentsBoundingBox(true, false);

	FVector Extend = (Bounds.Max - Bounds.Min) * 0.5f;
	FVector Center = Bounds.Min + Extend;
	DrawDebugBox(GetWorld(), Center, Extend, FColor::Red);
	
	TArray<FVector> Corners;
	Corners.Add(Bounds.Min);
	Corners.Add(FVector(Bounds.Min.X, Bounds.Min.Y, Bounds.Max.Z));
	Corners.Add(FVector(Bounds.Min.X, Bounds.Max.Y, Bounds.Min.Z));
	Corners.Add(FVector(Bounds.Min.X, Bounds.Max.Y, Bounds.Max.Z));
	Corners.Add(FVector(Bounds.Max.X, Bounds.Min.Y, Bounds.Min.Z));
	Corners.Add(FVector(Bounds.Max.X, Bounds.Min.Y, Bounds.Max.Z));
	Corners.Add(FVector(Bounds.Max.X, Bounds.Max.Y, Bounds.Min.Z));
	Corners.Add(Bounds.Max);
	
	// Project 3D corners to 2D screen space
	FVector2D MinScreen(FLT_MAX, FLT_MAX);
	FVector2D MaxScreen(FLT_MIN, FLT_MIN);

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	for (const FVector& Corner : Corners)
	{
		FVector2D ScreenPos;
		if (UGameplayStatics::ProjectWorldToScreen(PC, Corner, ScreenPos))
		{
			// Update min and max screen coordinates
			MinScreen.X = FMath::Min(MinScreen.X, ScreenPos.X);
			MinScreen.Y = FMath::Min(MinScreen.Y, ScreenPos.Y);
			MaxScreen.X = FMath::Max(MaxScreen.X, ScreenPos.X);
			MaxScreen.Y = FMath::Max(MaxScreen.Y, ScreenPos.Y);
		}
	}

	return FBox2d(MinScreen, MaxScreen);
}

void UHackableActorComponent::BeginPlay()
{
	Super::BeginPlay();
}
