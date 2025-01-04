// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TerminalCommand.generated.h"

USTRUCT(BlueprintType)
struct FTerminalCommandResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Output;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSuccess = false;	
};

UCLASS(Abstract, Blueprintable)
class PROJECTMOROCCO_API UTerminalCommand : public UObject
{
	GENERATED_BODY()

public:
	void Execute();

	UPROPERTY(EditDefaultsOnly, Category = "Terminal")
	FString CommandName;
	
protected:
	virtual void ExecuteImplementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Terminal")
	void BP_ExecuteImplementation();
	
};
