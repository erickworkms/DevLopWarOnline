// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPrincipalGameMode.h"
#include "GameFramework/HUD.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Estruturas/Struct.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudMenuPrincipal"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
}

void AMenuPrincipalGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (DefaultPlayerController)
	{
		DefaultPlayerController->bShowMouseCursor = true;
		DefaultPlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;
	}
}

void AMenuPrincipalGameMode::CriaSalaHost(int32 NumeroJogador,int32 CenarioEscolhido,FString NomeSala)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInt = OnlineSubsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			// Configurações da sala, como nome, mapa, etc.
			SessionSettings.bIsLANMatch = false;
			SessionSettings.bUsesPresence = true;
			SessionSettings.NumPublicConnections = NumeroJogador;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bAllowInvites = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings.Settings.Add(FName(TEXT("SessionName")), FVariantData(NomeSala));
			switch (CenarioEscolhido)
			{
			case 0:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Mapas/MapaJogavel"));
				break;
			case 1:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Mapas/MapaJogavel"));
				break;
			case 2:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Mapas/MapaJogavel"));
				break;
			default:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Mapas/MapaJogavel"));
				break;
			}
	

			FString teste;
			FString teste2;
			SessionSettings.Get(SETTING_MAPNAME,teste);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome de mapa :"+teste);
			SessionSettings.Get(FName(TEXT("SessionName")),teste2);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome SessionName :"+teste2);
			//SessionInt->TriggerOnSessionUserInviteAcceptedDelegates(0, TEXT("CustomEventName"), FOnlineSessionSearchResult());
			SessionInt->CreateSession(0, FName(*NomeSala), SessionSettings);
			GetWorld()->ServerTravel("/Game/Mapas/SalaEsperaPartida?listen");
		}
	}
}

void AMenuPrincipalGameMode::ProcuraSalaHost()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = true; 
			SessionSearch->MaxSearchResults = 20; 

			OnFindSessionsCompleteDelegate.BindUFunction(this, FName("OnFindSessionsComplete"));
			SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void AMenuPrincipalGameMode::OnFindSessionsComplete(bool Conectou)
{
	if (Conectou)
	{
		FoundSessions = SessionSearch->SearchResults;
		// Verificar se há resultados de pesquisa antes de chamar a função de conexão
		if (SessionSearch->SearchResults.Num() > 0)
		{
			ConectaSalaHost(SessionSearch->SearchResults[0]);
		}
	}
	else
	{
		// Lidar com falha na pesquisa de sessões
	}
}

void AMenuPrincipalGameMode::ProcuraSalaHostLista()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = true; 
			SessionSearch->MaxSearchResults = 20;
			OnFindSessionsCompleteDelegate.BindUFunction(hudDetectada, FName("OnFindSessionsComplete"));
			SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void AMenuPrincipalGameMode::ConectaSalaHost(const FOnlineSessionSearchResult& SearchResult)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
		                                 UKismetStringLibrary::Conv_BoolToString(SessionInterface.IsValid()) +
		                                 "sessionInterface");
		if (SessionInterface.IsValid())
		{			
			 // FName SessionName;
			 // SearchResult.Session.SessionSettings.Get(FName("SessionName"), SessionName);
			 //
			OnJoinSessionCompleteDelegate.BindUObject(this, &AMenuPrincipalGameMode::OnJoinSessionComplete);
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			SessionInterface->JoinSession(0, "SessionName", SearchResult);
		}
	}
}
void AMenuPrincipalGameMode::ConectaSalaID(FName sessao,int32 idPesquisa)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{			
			OnJoinSessionCompleteDelegate.BindUObject(this, &AMenuPrincipalGameMode::OnJoinSessionComplete);
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			SessionInterface->JoinSession(0, sessao, SessionSearch->SearchResults[idPesquisa]);
		}
	}
}
void AMenuPrincipalGameMode::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UNetConnection* Connection = PlayerController->GetNetConnection();
		
		HandleJoinSession(Connection);
	}
	else
	{
		// Lógica para lidar com falha na junção à sessão
	}

	// Remover o callback para evitar chamadas adicionais
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
		}
	}
}

void AMenuPrincipalGameMode::HandleJoinSession(UNetConnection* Conexao)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "achou a conexao com o controle");
	// Obtém o nome do cenário que o servidor deseja carregar
	FString MapName = "192.168.64.1"; // Substitua com o nome do seu cenário

	// Inicia a transição para o novo cenário no cliente
	PlayerController->ClientTravel(MapName, ETravelType::TRAVEL_Absolute);
}

void AMenuPrincipalGameMode::DeslogarJogador()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TelaLogin"));
}

void AMenuPrincipalGameMode::RetornaBuscar()
{
	FString ResultsString;
	FString sala;
	
	GeraDados.Empty();
	GeraDados.SetNum(SessionSearch->SearchResults.Num());
	for (int i= 0; i < SessionSearch->SearchResults.Num();i++)
	{
		GeraDados[i].ip = SessionSearch->SearchResults[i].GetSessionIdStr();
		GeraDados[i].JogadoresSala =SessionSearch->SearchResults[i].Session.SessionSettings.NumPublicConnections;
		GeraDados[i].MaxJogadores = SessionSearch->SearchResults[i].Session.SessionSettings.NumPublicConnections;
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName(TEXT("SessionName")), GeraDados[i].NomeSala);
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(SETTING_MAPNAME, GeraDados[i].Cenario);
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(SETTING_MAPNAME,ResultsString);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome de mapa :"+ResultsString);
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName(TEXT("SessionName")),sala);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome SessionName :"+sala);
		// FString SessionInfo = FString::Printf(
		// 	TEXT("Nome Sala: %s,Cenario: %s,Session ID: %s, Num Players: %d,Num Players na sala: %d"), *GeraDados[i].NomeSala, *GeraDados[i].Cenario, *GeraDados[i].ip,
		// 	GeraDados[i].MaxJogadores,GeraDados[i].JogadoresSala);
		//
		// ResultsString += SessionInfo + TEXT("\n");
	}
}
