//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MenuPrincipalGameMode.h"

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
