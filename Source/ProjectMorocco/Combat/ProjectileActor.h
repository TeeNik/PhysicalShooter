// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class PROJECTMOROCCO_API AProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	
	AProjectileActor();

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> CollisionComponent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnHit")
	void BP_OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;


};
