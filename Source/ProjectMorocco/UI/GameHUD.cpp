// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "ProjectMorocco/Hacking/Terminal/UI/TerminalWidget.h"

void AGameHUD::ShowTerminal()
{
	TerminalWidget->SetVisibility(ESlateVisibility::Visible);
	
	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(TerminalWidget->TakeWidget());
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
}

void AGameHUD::CloseTerminal()
{
	TerminalWidget->SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly{});
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	//Terminal = NewObject<UTerminal>(this);
	TerminalWidget = Cast<UTerminalWidget>(CreateWidget<UUserWidget>(GetWorld(), TerminalWidgetClass));
	TerminalWidget->AddToViewport();
	TerminalWidget->SetVisibility(ESlateVisibility::Collapsed);
}
