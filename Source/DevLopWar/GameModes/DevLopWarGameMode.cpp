//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWarGameMode.h"
#include "DevLopWar/Controles/GamePlayController.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

ADevLopWarGameMode::ADevLopWarGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/DevLopWar.Jogador_Base'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = NULL;
	}
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudGameplay"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	PlayerControllerClass = AGamePlayController::StaticClass();
}

void ADevLopWarGameMode::BeginPlay()
{
	Super::BeginPlay();
}
