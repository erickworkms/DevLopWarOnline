//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWarGameMode.h"
#include "DevLopWar/Controles/GamePlayController.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/Personagens/NPC/NPC_Base.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "GameFramework/HUD.h"
#include "Net/UnrealNetwork.h"
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
}

void ADevLopWarGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio1);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio2);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio3);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio4);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio1Dono);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio2Dono);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio3Dono);
	DOREPLIFETIME(ADevLopWarGameMode, VidaTerritorio4Dono);
	DOREPLIFETIME(ADevLopWarGameMode, TimeVencedor);
	
}


void ADevLopWarGameMode::ContadorTempo_Implementation()
{
	if (TempoJogo > 0.00001)
	{
		TempoJogo -= 0.1;
		GameStateServer->SetTempoJogo(TempoJogo);
	}
	else
	{
		TempoJogo = 0;
		GameStateServer->SetTempoJogo(TempoJogo);
	}
}

void ADevLopWarGameMode::AdicionaJogadorTime(const FString& NomeJogador, const ETime& Time)
{
	FInformacaoJogador dados;
	dados.Nome = NomeJogador;
	dados.Time = Time;
	Jogadores.Add(dados);
}

void ADevLopWarGameMode::RemoveJogadorTime(const FString& NomeJogador)
{
	for (int32 i = 0; i < Jogadores.Num(); ++i)
	{
		if (Jogadores[i].Nome.Equals(NomeJogador, ESearchCase::IgnoreCase))
		{
			Jogadores.RemoveAt(i);
			break;
		}
	}
}

void ADevLopWarGameMode::AcessaInformacoesTime(TArray<APlayerController*> ListaJogadores)
{
	for (int i=0;i < ListaJogadores.Num();i++)
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(ListaJogadores[i]);
		FInformacaoJogadorGameplay InfAux;
		InfAux.NumZumbiesMortos = PlayerState->GetNumZumbiesMortos();
		InfAux.NumJogadoresMortos = PlayerState->GetNumJogadoresMortos();
		InfAux.NumMortes = PlayerState->GetNumMortes();
		InfAux.TimeEscolhido = PlayerState->GetTimeEscolhido();
		InformacaoGameplay.Add(InfAux);
	}
}

void ADevLopWarGameMode::AlterarNumZumbiesMortos_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].NumZumbiesMortos++;
			PlayerState->SetNumZumbiesMortos(InformacaoGameplay[Index].NumZumbiesMortos);
		}
	}
}

void ADevLopWarGameMode::AlterarNumJogadoresMortos_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].NumJogadoresMortos++;
			PlayerState->SetNumJogadoresMortos(InformacaoGameplay[Index].NumJogadoresMortos);
		}
	}
}

void ADevLopWarGameMode::AlterarNumMortes_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerStateLocal = Cast<ADevOpPlayerState>(JogadoresSala[Index]->PlayerState);
		if (IsValid(PlayerStateLocal))
		{
			InformacaoGameplay[Index].NumMortes++;
			PlayerStateLocal->SetNumMortes(InformacaoGameplay[Index].NumMortes);
		}
	}
}

void ADevLopWarGameMode::AlterarTimeEscolhido_Implementation(int32 Index,ETime Time)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].TimeEscolhido = Time;
			PlayerState->SetTimeEscolhido(InformacaoGameplay[Index].TimeEscolhido);
		}
	}
}

void ADevLopWarGameMode::DanoAtaqueProjetil_Implementation(AActor* DonoProjetil, AActor* InimigoDetectado,AActor* Projetil)
{
	AJogador_Base* Jogador_Detectado = Cast<AJogador_Base>(InimigoDetectado);
	AJogador_Base* Inimigo = Cast<AJogador_Base>(DonoProjetil);
	ANPC_Base* NPC_Detectado = Cast<ANPC_Base>(InimigoDetectado);

	int DonoIndex = 0;
	int AlvoIndex = 0;
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"este é o jogador numero 0 : "+JogadoresSala[0]->GetName());
	
	if (IsValid(Jogador_Detectado))
	{
		if (Jogador_Detectado->Vida > 0)
		{
			for (int i=0;i < JogadoresSala.Num();i++)
			{
				if (IsValid(JogadoresSala[i]))
				{
					if (JogadoresSala[i] == Jogador_Detectado->GetController())
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Jogador_Detectado "+Jogador_Detectado->GetController()->GetName() + " esse é o indice "+FString::FromInt(i));

						AlvoIndex = i;
					}
					else if (JogadoresSala[i] == Inimigo->GetController())
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Inimigo "+Inimigo->GetController()->GetName());

						DonoIndex = i;
					}
				}
			}
			Jogador_Detectado->Vida -= Inimigo->QuantidadeDano;
				
			if (Jogador_Detectado->Vida <= 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,FString::FromInt(DonoIndex));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,FString::FromInt(AlvoIndex));
				AlterarNumJogadoresMortos(DonoIndex);
				AlterarNumMortes(AlvoIndex);
			}
		}
		Projetil->Destroy();
	}

	
	if (IsValid(NPC_Detectado))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
												 InimigoDetectado->GetName() + "bala" + GetName());
		NPC_Detectado->Vida -= 10;
		Projetil->Destroy();
	}
	else if (InimigoDetectado != DonoProjetil)
	{
		Projetil->Destroy();
	}
}
