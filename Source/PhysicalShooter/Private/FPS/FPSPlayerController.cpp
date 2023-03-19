#include "FPS/FPSPlayerController.h"
#include "AbilitySystemComponent.h"
#include "FPSCharacter.h"

void AFPSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//const AFPSCharacter* character = Cast<AFPSCharacter>(InPawn);
	//if(IsValid(character))
	//{
	//	UAbilitySystemComponent* asc = Cast<UAbilitySystemComponent>(character->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	//	if(IsValid(asc))
	//	{
	//		asc->InitAbilityActorInfo(this, InPawn);
	//	}
	//}
}
