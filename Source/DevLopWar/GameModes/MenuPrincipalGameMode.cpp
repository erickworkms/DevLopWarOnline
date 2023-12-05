//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "MenuPrincipalGameMode.h"

#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Estruturas/Struct.h"
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
	APlayerController* Controle = UGameplayStatics::GetPlayerController(this, 0);

	if (Controle)
	{
		Controle->bShowMouseCursor = true;
		Controle->DefaultMouseCursor = EMouseCursor::Crosshairs;
		SeuGameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	}
}

void AMenuPrincipalGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMenuPrincipalGameMode::CriaSalaHost(int32 NumeroJogador,int32 CenarioEscolhido,FString NomeSala)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInt = OnlineSubsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			// Configurações da sala, como nome, mapa, etc.
			SessionSettings.bIsLANMatch = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.NumPublicConnections = NumeroJogador;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bAllowInvites = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings.Settings.Add(FName(TEXT("SessionName")), FVariantData(NomeSala));
			SessionSettings.Set(NAME_GameSession, FString(NomeSala));
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

			SessionInt->CreateSession(0, FName(*NomeSala), SessionSettings);
			SeuGameInstance->SessionSettings = SessionSettings;
			SeuGameInstance->SessionInt = SessionInt;
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

		if (SessionInterface.IsValid())
		{			
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
	}
	
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
	// Obtém o nome do cenário que o servidor deseja carregar
	FString MapName = "192.168.15.180";

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
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome de mapa :"+ResultsString);
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName(TEXT("SessionName")),sala);
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome SessionName :"+sala);
		// // FString SessionInfo = FString::Printf(
		// 	TEXT("Nome Sala: %s,Cenario: %s,Session ID: %s, Num Players: %d,Num Players na sala: %d"), *GeraDados[i].NomeSala, *GeraDados[i].Cenario, *GeraDados[i].ip,
		// 	GeraDados[i].MaxJogadores,GeraDados[i].JogadoresSala);
		//
		// ResultsString += SessionInfo + TEXT("\n");
	}
}
