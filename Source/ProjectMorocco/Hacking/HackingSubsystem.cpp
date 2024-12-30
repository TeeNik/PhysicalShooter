// Fill out your copyright notice in the Description page of Project Settings.

#include "HackingSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectMorocco/UI/GameHUD.h"
#include "Terminal/Terminal.h"

void UHackingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Terminal = NewObject<UTerminal>(this);
}

void UHackingSubsystem::OpenTerminal()
{
	auto* HUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	HUD->ShowTerminal();
	OnHackingStateChanged.Broadcast(true);
}

void UHackingSubsystem::CloseTerminal()
{
	auto* HUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	HUD->CloseTerminal();
	OnHackingStateChanged.Broadcast(false);
}

void UHackingSubsystem::ExecuteCommand(const FString& Command)
{
	Terminal->ExecuteCommand(Command);
}
