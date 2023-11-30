// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "DevLopWarGameInstance.h"
#include "DevOpPlayerState.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Kismet/GameplayStatics.h"
#include "Huds/BaseHudMenuPrincipal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Net/UnrealNetwork.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudTelaLobby"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	//PlayerControllerClass = ALobbyController::StaticClass();
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
	OnPlayerJoined.Broadcast(NovoJogador);
}

void ALobbyGameMode::IniciaPartida()
{
	GetWorld()->ServerTravel("/Game/Mapas/MapaJogavel?listen");
}

void ALobbyGameMode::VerEntradaLogin()
{
	OnPlayerJoined.AddDynamic(hudDetectada, &ABaseHudMenuPrincipal::HandlePlayerJoined);
}


void ALobbyGameMode::DesconectaCliente_Implementation(APlayerController* PlayerController, int32 Id)
{
	if (IsValid(JogadoresSala[Id]) && GetLocalRole() == ROLE_Authority)
	{
		JogadoresSala[Id]->ClientTravel("/Game/Mapas/TelaInicial", ETravelType::TRAVEL_Absolute);
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

void ALobbyGameMode::ExcluirSala(APlayerController* Jogador)
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
}

void ALobbyGameMode::EnviarMensagemChat_Implementation(const FString& mensagem)
{
	UWorld* World = GetWorld();
	check(World);
	if (GetLocalRole() == ROLE_Authority)
	{
		APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		ADevOpPlayerState* PlayerStateProprio = Cast<ADevOpPlayerState>(DefaultPlayerController->PlayerState);
		if (IsValid(PlayerStateProprio))
		{
			if (IsValid(PlayerStateProprio->hudDetectada))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,"detectou" + DefaultPlayerController->GetName() +" "+PlayerStateProprio->hudDetectada->GetName());
				PlayerStateProprio->hudDetectada->EnviaMensagemChat(DefaultPlayerController->GetName(),mensagem);
			}
		}
		for (int i = 0; i < JogadoresSala.Num();i++)
		{
			if (IsValid(JogadoresSala[i]))
			{
				ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[i]->PlayerState);
				if (IsValid(PlayerState->hudDetectada))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,"detectou" + JogadoresSala[i]->GetName() +" "+PlayerState->GetName());
				}
			}
		}
		// for (FConstControllerIterator it = World->GetControllerIterator(); it; ++it)
		// {
		// 	if (APlayerController* PlayerController = Cast<APlayerController>(*it))
		// 		if (IsValid(PlayerController))
		// 		{
		// 			ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(PlayerController->PlayerState);
		// 			if (IsValid(PlayerState))
		// 			{
		//
		//
		// 				if (IsValid(PlayerState->hudDetectada))
		// 				{
		// 					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
		// 							 "Este é o teste com nome de mapa :" + PlayerController->
		// 							 GetName() + PlayerState->GetName());
		// 					PlayerState->hudDetectada->EnviaMensagemChat(PlayerController->GetName(),mensagem);
		// 				}
		// 				// 
		// 			}
		// 		}
		// }
	}
}
