// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HackableActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMOROCCO_API UHackableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHackableActorComponent();

	UFUNCTION(BlueprintPure)
	FBox2D GetScreenBounds() const;

protected:
	virtual void BeginPlay() override;

		
};
