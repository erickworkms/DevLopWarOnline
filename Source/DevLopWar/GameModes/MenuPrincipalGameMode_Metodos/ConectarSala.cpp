//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MenuPrincipalGameMode.h"
#include "Kismet/GameplayStatics.h"

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
		HandleJoinSession();
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


void AMenuPrincipalGameMode::HandleJoinSession()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Inicia a transição para o novo cenário no cliente
	PlayerController->ClientTravel(EnderecoIPBruto, ETravelType::TRAVEL_Absolute);
}
