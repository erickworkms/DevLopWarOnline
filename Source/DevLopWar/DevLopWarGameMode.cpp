// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevLopWarGameMode.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

ADevLopWarGameMode::ADevLopWarGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/DevLopWar.Jogador_Base'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudGameplay"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
}

void ADevLopWarGameMode::BeginPlay()
{
	Super::BeginPlay();
}
