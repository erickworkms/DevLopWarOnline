//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Common/UdpSocketBuilder.h"
#include "Containers/UnrealString.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MenuPrincipalGameMode.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

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

void AMenuPrincipalGameMode::ProcuraSalaHostLista(FString IP, int Porta)
{
	const TCHAR* EnderecoIP = *IP;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

			if (SocketSubsystem)
			{
				FSocket* TCPSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCP"), false);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Chegou no subsystem");

				if (TCPSocket)
				{
					// Conecta ao servidor
					FIPv4Address ServidorIP;
					FIPv4Address::Parse(EnderecoIP, ServidorIP);
					FIPv4Endpoint Endpoint(ServidorIP, (uint16)Porta);

					FSocket* ListenSocket = FUdpSocketBuilder(TEXT("TcpSocket")).AsReusable();
					ListenSocket->Bind(*SocketSubsystem->CreateInternetAddr(Endpoint.Address.Value,Endpoint.Port));
					ListenSocket->Listen(8);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Antes da conexao");

					if (ListenSocket->Connect(*Endpoint.ToInternetAddr()))
					{
						SessionSearch = MakeShareable(new FOnlineSessionSearch());
						SessionSearch->bIsLanQuery = false;
						SessionSearch->MaxSearchResults = 20;
						OnFindSessionsCompleteDelegate.BindUFunction(hudDetectada, FName("OnFindSessionsComplete"));
						SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
						SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Chegou na conexao");
						TCPSocket->Close();
						ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(TCPSocket);
					}
					else
					{
						ESocketConnectionState ConnectionState = ListenSocket->GetConnectionState();
						//ESocketConnectionState ConnectionState = TCPSocket->GetDescription();
						FString EstadoConexaoString = GetStringFromConnectionState(ConnectionState);

						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"este é o erro");
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,EstadoConexaoString);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ListenSocket->GetPortNo()));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Endpoint.ToString());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ListenSocket->GetPeerAddress(*Endpoint.ToInternetAddr())));

					}
				}
			}
		}
	}
}

FString AMenuPrincipalGameMode::GetStringFromConnectionState(ESocketConnectionState ConnectionState)
{
	switch (ConnectionState)
	{
	case SCS_NotConnected:
		return TEXT("Not Connected");
	case SCS_Connected:
		return TEXT("Connected");
	case SCS_ConnectionError:
		return TEXT("Connection Error");
		// Adicione mais casos conforme necessário
		default:
			return TEXT("Unknown");
	}
}