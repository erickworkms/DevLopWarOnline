// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "Huds/BaseHudMenuPrincipal.h"
#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudTelaLobby"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	
	bReplicates = true;
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	if (DefaultPlayerController)
	{
		DefaultPlayerController->bShowMouseCursor = true;
		DefaultPlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;
		//JogadoresSala.Add(DefaultPlayerController);
		PostLogin(DefaultPlayerController);
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NovoJogador)
{
	Super::PostLogin(NovoJogador);
	OnPlayerJoined.Broadcast(NovoJogador);
	JogadoresSala.Add(NovoJogador);
}

void ALobbyGameMode::IniciaPartida()
{
	GetWorld()->ServerTravel("/Game/Mapas/MapaJogavel?listen");
}

void ALobbyGameMode::EnviarMensagemChat(FString mensagem)
{
}

void ALobbyGameMode::VerEntradaLogin()
{
	OnPlayerJoined.AddDynamic(hudDetectada,&ABaseHudMenuPrincipal::HandlePlayerJoined);
}
