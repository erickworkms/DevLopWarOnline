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
		VerEntradaLogin();
	}
	JogoInicializado = false;
}

void ALobbyGameMode::PostLogin(APlayerController* NovoJogador)
{
	Super::PostLogin(NovoJogador);
	
	ALobbyController* Controle = Cast<ALobbyController>(NovoJogador);

	if (!JogoInicializado)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("AtrasarControle"), Controle, NovoJogador);

		FTimerHandle PostLoginTimerHandle;
		GetWorldTimerManager().SetTimer(PostLoginTimerHandle, TimerDelegate, 0.5f, false);
	}
	else
	{
		AtrasarControle(Controle,NovoJogador);
	}
}

void ALobbyGameMode::AtrasarControle(ALobbyController* Controle, APlayerController* NovoJogador)
{
	Controle->AdicionaDadosInstance(JogadoresSala.Num());
    
	FInformacaoJogador InformacaoJogador;
	InformacaoJogador.Nome = Controle->GetUsuario();
	InformacaoJogador.Time = ETime::Nenhum;
        
	Jogadores.Add(InformacaoJogador);
	JogadoresSalaNome.Add(Controle->GetUsuario());
	JogadoresSala.Add(NovoJogador);
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

void ALobbyGameMode::AtualizaListaPlayers_Implementation()
{
	UWorld* World = GetWorld();
	check(World);

	APlayerController* Controle = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ALobbyController* Servidor = Cast<ALobbyController>(Controle);

	//PostLogin(Controle);
	TArray<APlayerController*> JogadoresEncontrados;
	JogadoresEncontrados.Add(Controle);
	for (FConstControllerIterator it = World->GetControllerIterator(); it; ++it)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*it))
			if (IsValid(PlayerController))
			{
				ALobbyController* PlayerEncontrado = Cast<ALobbyController>(PlayerController);
					if (Servidor != PlayerEncontrado)
					{
						JogadoresEncontrados.Add(PlayerEncontrado);
					}					
			}
	}
	TArray<FTimerDelegate> TimerDelegate;
	TimerDelegate.SetNum(JogadoresEncontrados.Num());
	TArray<FTimerHandle> PostLoginTimerHandle;
	PostLoginTimerHandle.SetNum(JogadoresEncontrados.Num());
	for (int i = 0; i < JogadoresEncontrados.Num();i++)
	{
		TimerDelegate[i].BindUFunction(this, FName("PostLogin"), JogadoresEncontrados[i]);
		GetWorldTimerManager().SetTimer(PostLoginTimerHandle[i], TimerDelegate[i], (0.5f+i)/2, false);
	}
}

void ALobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSala);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSalaNome);
}
