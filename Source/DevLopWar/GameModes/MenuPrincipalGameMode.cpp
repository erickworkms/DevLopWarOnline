//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "MenuPrincipalGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "OnlineSessionSettings.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Estruturas/Struct.h"
#include "Kismet/GameplayStatics.h"


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
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Este é o teste com nome SessionName :"+sala);
		// // FString SessionInfo = FString::Printf(
		// 	TEXT("Nome Sala: %s,Cenario: %s,Session ID: %s, Num Players: %d,Num Players na sala: %d"), *GeraDados[i].NomeSala, *GeraDados[i].Cenario, *GeraDados[i].ip,
		// 	GeraDados[i].MaxJogadores,GeraDados[i].JogadoresSala);
		//
		// ResultsString += SessionInfo + TEXT("\n");
	}
}

