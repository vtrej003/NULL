// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodenameNullGameMode.h"
#include "CodenameNullCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACodenameNullGameMode::ACodenameNullGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
