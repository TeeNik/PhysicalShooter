// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PMGameStateBase.generated.h"

class UHackingGameStateComponent;

UCLASS(Abstract, Blueprintable)
class PROJECTMOROCCO_API APMGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	APMGameStateBase();
	
	UFUNCTION(BlueprintPure, Category="Hacking")
	UHackingGameStateComponent* GetHackingGameStateComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hacking")
	TObjectPtr<UHackingGameStateComponent> HackingGameStateComponent;
	
};
