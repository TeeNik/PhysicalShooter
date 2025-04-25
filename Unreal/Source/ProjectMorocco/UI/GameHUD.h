// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UTerminalWidget;

UCLASS()
class PROJECTMOROCCO_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowTerminal();
	void CloseTerminal();
	
	UPROPERTY(Transient)
	UTerminalWidget* TerminalWidget;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Terminal")
	TSubclassOf<UTerminalWidget> TerminalWidgetClass;
	
};
