// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EX3_Waldemar_ZeitlerGameMode.h"
#include "VRPawn.h"
#include "UObject/ConstructorHelpers.h"

AEX3_Waldemar_ZeitlerGameMode::AEX3_Waldemar_ZeitlerGameMode()
{
    // The VRPawn shall be the default pawn and spawn with the player start
    DefaultPawnClass = AVRPawn::StaticClass();
}
