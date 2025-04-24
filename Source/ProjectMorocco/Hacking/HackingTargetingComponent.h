// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HackingTargetingComponent.generated.h"


class UTerminalWidget;
class UTerminal;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMOROCCO_API UHackingTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHackingTargetingComponent();

	UFUNCTION(BlueprintPure)
	AActor* GetCurrentTarget() const;

	UFUNCTION(BlueprintPure)
	bool GetMinMaxOnScreen(FVector& Min, FVector& Max);
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	
	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> CurrentTarget;


};
