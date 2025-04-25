// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

class AProjectileActor;

UCLASS(Abstract)
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

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "FirePressed")
	void BP_FirePressed();
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "FireReleased")
	void BP_FireReleased();
	
	UPROPERTY(EditDefaultsOnly, Category = "WeaponActor")
	TSubclassOf<AProjectileActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponActor")
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponActor")
	TObjectPtr<USceneComponent> MuzzleComponent;

};
