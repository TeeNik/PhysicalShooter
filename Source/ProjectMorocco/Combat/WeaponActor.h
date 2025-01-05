// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class PROJECTMOROCCO_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponActor();

	void FirePressed();
	void FireReleased();
	
	UFUNCTION(BlueprintPure, Category = "WeaponActor")
	FVector GetMuzzleLocation() const;

protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "WeaponActor")

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponActor")
	TObjectPtr<USceneComponent> MuzzleComponent;

};
