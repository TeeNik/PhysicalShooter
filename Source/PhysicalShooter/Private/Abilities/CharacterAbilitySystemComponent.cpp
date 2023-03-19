#include "Abilities/CharacterAbilitySystemComponent.h"

void UCharacterAbilitySystemComponent::TakeDamage(UCharacterAbilitySystemComponent* SourceASC, float Damage,	float RawDamage)
{
	OnDamageReceived.Broadcast(SourceASC, Damage, RawDamage);
}
