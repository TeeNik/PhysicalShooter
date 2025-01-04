// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Terminal.generated.h"

UCLASS()
class PROJECTMOROCCO_API UTerminal : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();
	void ExecuteCommand(const FString& String);
	const TArray<UClass*>& GetAllCommands() const;

private:
	void CollectCommands();

	UPROPERTY(Transient)
	TMap<FString, UClass*> CommandsByName;
	
	UPROPERTY(Transient)
	TArray<UClass*> CommandClasses;
	
};
