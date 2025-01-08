// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingGameStateComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectMorocco/Hacking/Terminal/Terminal.h"
#include "ProjectMorocco/UI/GameHUD.h"

UHackingGameStateComponent::UHackingGameStateComponent()
{
}

void UHackingGameStateComponent::OpenTerminal()
{
	auto* HUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	HUD->ShowTerminal();
	OnHackingStateChanged.Broadcast(true);
}

void UHackingGameStateComponent::CloseTerminal()
{
	auto* HUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	HUD->CloseTerminal();
	OnHackingStateChanged.Broadcast(false);
}

void UHackingGameStateComponent::ExecuteCommand(const FString& Command)
{
	Terminal->ExecuteCommand(Command);
}

void UHackingGameStateComponent::BeginPlay()
{
	Super::BeginPlay();

	Terminal = NewObject<UTerminal>(this);
	Terminal->Initialize();
}
