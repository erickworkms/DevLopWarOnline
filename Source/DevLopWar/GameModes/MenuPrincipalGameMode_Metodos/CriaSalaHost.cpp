//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MenuPrincipalGameMode.h"


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
