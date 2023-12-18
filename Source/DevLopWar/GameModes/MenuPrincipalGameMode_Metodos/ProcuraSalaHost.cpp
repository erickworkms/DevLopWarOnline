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

void AMenuPrincipalGameMode::ProcuraSalaHost(FString IPEscolhido, int PortaEscolhida, bool Lan)
{
	EnderecoIP = *IPEscolhido;
	Porta = PortaEscolhida;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

			if (SocketSubsystem)
			{
				if (Lan)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"passou no nlan");

					SessionSearch = MakeShareable(new FOnlineSessionSearch());
					SessionSearch->bIsLanQuery = false;
					SessionSearch->MaxSearchResults = 20;
					OnFindSessionsCompleteDelegate.BindUFunction(this, FName("OnFindSessionsComplete"));
					SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
					SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
				}
				else
				{
					UDPSocket = FTcpSocketBuilder(TEXT("UDPSocket")).AsReusable();

					if (UDPSocket)
					{
						// Conecta ao servidor
						FIPv4Address ServidorIP;
						FIPv4Address::Parse(EnderecoIP, ServidorIP);
						FIPv4Endpoint Endpoint(ServidorIP, (uint16)Porta);


						UDPSocket->Bind(*SocketSubsystem->CreateInternetAddr(Endpoint.Address.Value, Endpoint.Port));
						UDPSocket->Listen(5);

						if (UDPSocket->Connect(*Endpoint.ToInternetAddr()))
						{
							SessionSearch = MakeShareable(new FOnlineSessionSearch());
							SessionSearch->bIsLanQuery = false;
							SessionSearch->MaxSearchResults = 20;
							OnFindSessionsCompleteDelegate.BindUFunction(this, FName("OnFindSessionsComplete"));
							SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
							SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
							// UDPSocket->Close();
							// ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
						}
						else
						{
							ESocketConnectionState ConnectionState = UDPSocket->GetConnectionState();
							FString EstadoConexaoString = GetStringFromConnectionState(ConnectionState);

							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "este é o erro");
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, EstadoConexaoString);
							UDPSocket->Close();
							ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
						}
					}
				}
			}
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

void AMenuPrincipalGameMode::ProcuraSalaHostLista(FString IPEscolhido, int PortaEscolhida, bool Lan)
{
	EnderecoIP = *IPEscolhido;
	Porta = PortaEscolhida;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

			if (SocketSubsystem)
			{
				if (Lan)
				{
					SessionSearch = MakeShareable(new FOnlineSessionSearch());
					SessionSearch->bIsLanQuery = true;
					SessionSearch->MaxSearchResults = 20;
					OnFindSessionsCompleteDelegate.BindUFunction(hudDetectada, FName("OnFindSessionsComplete"));
					SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
					SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
				}
				else
				{
					UDPSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCP"), false);
					//UDPSocket = FUdpSocketBuilder(TEXT("UDPSocket")).AsReusable();

					if (UDPSocket)
					{
						// Conecta ao servidor
						FIPv4Address ServidorIP;
						FIPv4Address::Parse(EnderecoIP, ServidorIP);
						FIPv4Endpoint Endpoint(ServidorIP, Porta);


						//UDPSocket->Bind(*SocketSubsystem->CreateInternetAddr(Endpoint.Address.Value,Endpoint.Port));
						UDPSocket->Listen(5);

						if (UDPSocket->Connect(*Endpoint.ToInternetAddr()))
						{
							SessionSearch = MakeShareable(new FOnlineSessionSearch());
							SessionSearch->bIsLanQuery = false;
							SessionSearch->MaxSearchResults = 20;
							OnFindSessionsCompleteDelegate.BindUFunction(hudDetectada, FName("OnFindSessionsComplete"));
							SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
							SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
							// UDPSocket->Close();
							// ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
						}
						else
						{
							ESocketConnectionState ConnectionState = UDPSocket->GetConnectionState();
							FString EstadoConexaoString = GetStringFromConnectionState(ConnectionState);

							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "este é o erro");
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, EstadoConexaoString);
							UDPSocket->Close();
							ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
						}
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
