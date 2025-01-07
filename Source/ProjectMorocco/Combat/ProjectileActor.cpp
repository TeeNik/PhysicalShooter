// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectileActor::AProjectileActor()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,	FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	Destroy();
}
