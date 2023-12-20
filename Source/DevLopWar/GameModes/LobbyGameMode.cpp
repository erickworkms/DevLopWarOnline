//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LobbyGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controles/LobbyController.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudTelaLobby"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	//DefaultPawnClass = ADevLopWarCharacter::StaticClass();
	PlayerControllerClass = ALobbyController::StaticClass();
	PlayerStateClass = ADevOpPlayerState::StaticClass();
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

		GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NovoJogador)
{
	Super::PostLogin(NovoJogador);
	JogadoresSala.Add(NovoJogador);
	
	ALobbyController* Controle = Cast<ALobbyController>(NovoJogador);
	
	Controle->AdicionaDadosInstance(JogadoresSala.Num() - 1);
	
	FInformacaoJogador InformacaoJogador;
	InformacaoJogador.Nome = Controle->Usuario;
	InformacaoJogador.Time = ETime::Nenhum;

	Jogadores.Add(InformacaoJogador);
	
	JogadoresSalaNome.Add(Controle->Usuario);
	
	OnPlayerJoined.Broadcast(NovoJogador);
}

void ALobbyGameMode::IniciaPartida()
{
	JogoInicializado = true;

	GameInstance->GeraDados = GeraDados;
	GameInstance->Jogadores = Jogadores;
	GameInstance->JogadoresSala = JogadoresSala;
	GameInstance->JogadoresSalaNome = JogadoresSalaNome;
	GameInstance->TotalJogadores = JogadoresSala.Num();
	GetWorld()->ServerTravel("/Game/Mapas/MapaJogavel?listen");
}

void ALobbyGameMode::VerEntradaLogin()
{
	OnPlayerJoined.AddDynamic(this, &ALobbyGameMode::HandlePlayerJoined);
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (GetLocalRole() == ROLE_Authority && !JogoInicializado)
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
		hudDetectada->AdicionaHudSalas(JogadoresSalaNome);
	}
}

void ALobbyGameMode::HandlePlayerJoined(APlayerController* PlayerController)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i=0;i < JogadoresSala.Num();i++)
		{
			if (IsValid(JogadoresSala[i]) && JogadoresSala[i] != PlayerController)
			{
				ALobbyController* Controle = Cast<ALobbyController>(JogadoresSala[i]);
				Controle->VerEntradaLogin(JogadoresSalaNome);
			}
			else if (IsValid(JogadoresSala[i]) && JogadoresSala[i] == PlayerController)
			{
				ValorIndexUsuarioAtraso = i;
				GetWorldTimerManager().SetTimer(Contador, this, &ALobbyGameMode::TimerHud, 0.25f,false);
			}
		}
	}
}

void ALobbyGameMode::TimerHud()
{
	ALobbyController* Controle = Cast<ALobbyController>(JogadoresSala[ValorIndexUsuarioAtraso]);
	Controle->VerEntradaLogin(JogadoresSalaNome);
	GetWorldTimerManager().ClearTimer(Contador);
}

void ALobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSala);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSalaNome);
}
