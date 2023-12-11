//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWarGameMode.h"
#include "DevLopWar/Controles/GamePlayController.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/Personagens/NPC/ObjetivoNPC.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "GameFramework/HUD.h"
#include "EngineUtils.h"
#include "DevLopWar/Personagens/NPC/NPC_Base.h"
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
	PlayerStateClass = ADevOpPlayerState::StaticClass();
	PlayerControllerClass = AGamePlayController::StaticClass();
	GameStateClass = ADevLopWarGameStateBase::StaticClass();

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADevLopWarGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStateServer = Cast<ADevLopWarGameStateBase>(GameState);
	GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());

	if (HasAuthority())
	{
		GeraDados = GameInstance->GeraDados;
		Jogadores = GameInstance->Jogadores;
		JogadoresSala.SetNum(GameInstance->TotalJogadores);
		InformacaoGameplay.SetNum(GameInstance->TotalJogadores);
		JogadoresSalaNome = GameInstance->JogadoresSalaNome;
		GetWorldTimerManager().SetTimer(Contador, this, &ADevLopWarGameMode::ContadorTempo, 0.1, true);
	}
	DetectaPontosObjetivo();
}

void ADevLopWarGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i=0;i < JogadoresSala.Num();i++)
		{
			if (IsValid(JogadoresSala[i]) && JogadoresSala[i] == Exiting)
			{
				JogadoresSalaNome.RemoveAt(i);
				JogadoresSala.RemoveAt(i);
				Jogadores.RemoveAt(i);
			}
		}
	}
}

void ADevLopWarGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void ADevLopWarGameMode::ContadorTempo_Implementation()
{
	if (!JogoFinalizado)
	{
		if (TempoJogo > 0.00001)
		{
			TempoJogo -= 0.1;
			GameStateServer->SetTempoJogo(TempoJogo);
		}
		else
		{
			JogoFinalizado = true;
			TempoJogo = 0;
			GameStateServer->SetTempoJogo(TempoJogo);
			GameStateServer->SetTimeVencedor();
			
			for (int i = 0; i < JogadoresSala.Num(); i++)
			{
				AGamePlayController* controle = Cast<AGamePlayController>(JogadoresSala[i]);
				if (IsValid(controle))
				{
					controle->AtivaHudFimPartida();
					controle->GetPawn()->Destroy();
				}
			}
			for (TActorIterator<ANPC_Base> It(GetWorld()); It; ++It)
			{
				ANPC_Base* NPC = *It;
		
				NPC->Destroy();
			}
			GetWorldTimerManager().ClearTimer(Contador);
		}
	}
}

void ADevLopWarGameMode::DetectaPontosObjetivo()
{
	UWorld* World = GetWorld();
	check(World);

	if (GetLocalRole() == ROLE_Authority)
	{
		for (TActorIterator<AObjetivoNPC> It(World); It; ++It)
		{
			if (AObjetivoNPC* Objetivo = Cast<AObjetivoNPC>(*It))
			{
				if (IsValid(Objetivo))
				{
					switch (Objetivo->IndexTerritorio)
					{
					case 1:
						GameStateServer->SetVidaTerritorio1(Objetivo->Vida);
						GameStateServer->SetDonoTerritorio1(Objetivo->TimeTerritorio);
						GameStateServer->SetBloqueioTerritorio1(Objetivo->EstaBloqueado);
						break;
					case 2:
						GameStateServer->SetVidaTerritorio2(Objetivo->Vida);
						GameStateServer->SetDonoTerritorio2(Objetivo->TimeTerritorio);
						GameStateServer->SetBloqueioTerritorio2(Objetivo->EstaBloqueado);
						break;
					case 3:
						GameStateServer->SetVidaTerritorio3(Objetivo->Vida);
						GameStateServer->SetDonoTerritorio3(Objetivo->TimeTerritorio);
						GameStateServer->SetBloqueioTerritorio3(Objetivo->EstaBloqueado);
						break;
					case 4:
						GameStateServer->SetVidaTerritorio4(Objetivo->Vida);
						GameStateServer->SetDonoTerritorio4(Objetivo->TimeTerritorio);
						GameStateServer->SetBloqueioTerritorio4(Objetivo->EstaBloqueado);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void ADevLopWarGameMode::RetornaLobby_Implementation()
{
	GetWorld()->ServerTravel("/Game/Mapas/SalaEsperaPartida?listen");
}

void ADevLopWarGameMode::ReativaPontosObjetivo_Implementation(int IndexObjetivo, bool EstadoBloqueio)
{
	switch (IndexObjetivo)
	{
	case 1:
		GameStateServer->SetBloqueioTerritorio1(EstadoBloqueio);
		break;
	case 2:
		GameStateServer->SetBloqueioTerritorio2(EstadoBloqueio);
		break;
	case 3:
		GameStateServer->SetBloqueioTerritorio3(EstadoBloqueio);
		break;
	case 4:
		GameStateServer->SetBloqueioTerritorio4(EstadoBloqueio);
		break;
	default:
		break;
	}
}
