//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LobbyGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
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

		SeuGameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NovoJogador)
{
	Super::PostLogin(NovoJogador);
	JogadoresSala.Add(NovoJogador);
	ALobbyController* Controle = Cast<ALobbyController>(NovoJogador);
	JogadoresSalaNome.Add(Controle->GetName());
	OnPlayerJoined.Broadcast(NovoJogador);
}

void ALobbyGameMode::IniciaPartida()
{
	GetWorld()->ServerTravel("/Game/Mapas/MapaJogavel?listen");
}

void ALobbyGameMode::VerEntradaLogin()
{
	OnPlayerJoined.AddDynamic(this, &ALobbyGameMode::HandlePlayerJoined);
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

void ALobbyGameMode::DesconectaCliente_Implementation(APlayerController* PlayerController, int32 Id)
{
	if (IsValid(JogadoresSala[Id]) && GetLocalRole() == ROLE_Authority)
	{
		JogadoresSala[Id]->ClientTravel("/Game/Mapas/TelaInicial", ETravelType::TRAVEL_Absolute);
		JogadoresSala.RemoveAt(Id);
		JogadoresSalaNome.RemoveAt(Id);
	}
	for (int i=0;i < JogadoresSala.Num();i++)
	{
		if (IsValid(JogadoresSala[i]))
		{
			ALobbyController* Controle = Cast<ALobbyController>(JogadoresSala[i]);
			Controle->VerEntradaLogin(JogadoresSalaNome);
		}
	}
}

bool ALobbyGameMode::DesconectaCliente_Validate(APlayerController* PlayerController, int32 Id)
{
	if (Id == 0 && GetLocalRole() == ROLE_Authority)
	{
		APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		DefaultPlayerController->ClientTravel("/Game/Mapas/TelaInicial", ETravelType::TRAVEL_Absolute);
	}
	else if (IsValid(JogadoresSala[Id]) && GetLocalRole() == ROLE_Authority)
	{
		return true;
	}
	return false;
}

void ALobbyGameMode::ExcluirSala()
{
	if (SeuGameInstance->SessionInt.IsValid())
	{
		FString NomeDaSala;
		SeuGameInstance->SessionSettings.Get(NAME_GameSession, NomeDaSala);
		SeuGameInstance->SessionInt->DestroySession(*NomeDaSala);
	}
}

void ALobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSala);
	DOREPLIFETIME(ALobbyGameMode,JogadoresSalaNome);
}

void ALobbyGameMode::EnviarMensagemChat_Implementation(const FString& mensagem)
{
	UWorld* World = GetWorld();
	check(World);
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < JogadoresSala.Num();i++)
		{
			if (IsValid(JogadoresSala[i]))
			{
				ALobbyController* PlayerState = Cast<ALobbyController>(JogadoresSala[i]);
				if (IsValid(PlayerState))
				{
					PlayerState->EnviarMensagemCliente(JogadoresSala[i]->GetName(),mensagem);
				}
			}
		}
	}
}
