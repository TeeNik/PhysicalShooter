// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterPlaygroundGameMode.h"
#include "ShooterPlaygroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterPlaygroundGameMode::AShooterPlaygroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
