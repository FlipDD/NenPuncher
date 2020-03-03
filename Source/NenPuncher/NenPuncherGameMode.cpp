// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NenPuncherGameMode.h"
#include "NenPuncherCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANenPuncherGameMode::ANenPuncherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/NenPuncherCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
