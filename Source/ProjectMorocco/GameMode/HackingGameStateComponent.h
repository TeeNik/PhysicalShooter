// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HackingGameStateComponent.generated.h"

class UTerminal;;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHackingStateChanged, bool, bActive);

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

	UPROPERTY(BlueprintAssignable, Category="Hacking")
	FOnHackingStateChanged OnHackingStateChanged;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
	UTerminal* Terminal;
	
};
