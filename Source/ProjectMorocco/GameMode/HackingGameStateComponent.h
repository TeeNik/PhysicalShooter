// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HackingGameStateComponent.generated.h"

struct FTerminalCommandResult;
class UTerminalCommand;
class UTerminal;;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHackingStateChanged, bool, bActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCommandExecuted, const FTerminalCommandResult&, CommandResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMOROCCO_API UHackingGameStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHackingGameStateComponent();

	UFUNCTION(BlueprintCallable)
	void OpenTerminal();
	UFUNCTION(BlueprintCallable)
	void CloseTerminal();

	UFUNCTION(Blueprintable)
	void ExecuteCommand(const FString& Command);

	const TArray<TSubclassOf<UTerminalCommand>>& GetCommandClasses() const;

	UPROPERTY(BlueprintAssignable, Category = "Hacking")
	FOnHackingStateChanged OnHackingStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hacking")
	FOnCommandExecuted OnCommandExecuted;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hacking")
	TArray<TSubclassOf<UTerminalCommand>> CommandClasses;

private:
	UPROPERTY(Transient)
	UTerminal* Terminal;
	
};
