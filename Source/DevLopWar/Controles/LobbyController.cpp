//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "Net/UnrealNetwork.h"

void ALobbyController::EnviarMensagemServer_Implementation(const FString& nome, const FString& mensagem)
{
	if (HasAuthority()) // Verifica se este é o servidor
	{
		ALobbyGameMode* GameMode = GetWorld()->GetAuthGameMode<ALobbyGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->EnviarMensagemChat(mensagem);
		}
	}
}

void ALobbyController::EnviarMensagemCliente_Implementation(const FString& nome, const FString& mensagem)
{
	HudChat->EnviaMensagemChat(mensagem);
}

void ALobbyController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

ALobbyController::ALobbyController()
{
	PlayerState = GetPlayerState<ADevOpPlayerState>();
	bReplicates = true;
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALobbyController::AdicionaDadosInstance_Implementation(int32 IndexJogador)
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	PlayerInstance->ControleJogador = this;
	PlayerInstance->IndexJogador = IndexJogador;
	PlayerInstance->Time = ETime::Agil;
}
void ALobbyController::AlteraTimeInstance_Implementation(ETime Time)
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	PlayerInstance->Time = Time;
}

void ALobbyController::VerificaDadosInstance_Implementation()
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,"Este é a instance no final "+PlayerInstance->GetName() + FString::FromInt(PlayerInstance->IndexJogador));
}

void ALobbyController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyController, HudChat);
}

void ALobbyController::VerEntradaLogin_Implementation(const TArray<FString>& JogadoresSalaNome)
{
	if (IsValid(HudChat))
	{
		HudChat->AdicionaHudSalas(JogadoresSalaNome);
	}
}
