#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UCharacterAbilitySystemComponent*, SourceASC, float, Damage, float, RawDamage);

UCLASS()
class PHYSICALSHOOTER_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	UPROPERTY()
	FReceivedDamageDelegate OnDamageReceived;

	void TakeDamage(UCharacterAbilitySystemComponent* SourceASC, float Damage, float RawDamage);
	
};
