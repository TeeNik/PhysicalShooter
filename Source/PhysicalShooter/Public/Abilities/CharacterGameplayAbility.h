// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PhysicalShooter/PhysicalShooter.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICALSHOOTER_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCharacterGameplayAbility();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	AbilityID InputID = AbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	AbilityID ID = AbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
