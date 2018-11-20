// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EX2_Waldemar_ZeitlerGameMode.h"
#include "EX2_Waldemar_ZeitlerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEX2_Waldemar_ZeitlerGameMode::AEX2_Waldemar_ZeitlerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
