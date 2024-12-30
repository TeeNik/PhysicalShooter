// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HackingSubsystem.generated.h"

class UTerminalWidget;
class UTerminal;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHackingStateChanged, bool, bActive);

UCLASS(Abstract, Blueprintable)
class PROJECTMOROCCO_API UHackingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void OpenTerminal();
	UFUNCTION(BlueprintCallable)
	void CloseTerminal();

	UFUNCTION(Blueprintable)
	void ExecuteCommand(const FString& Command);

	UPROPERTY(BlueprintAssignable, Category="Hacking")
	FOnHackingStateChanged OnHackingStateChanged;

protected:

private:
	UPROPERTY(Transient)
	UTerminal* Terminal;
	
};
