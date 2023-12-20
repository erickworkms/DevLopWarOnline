//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "JsonObjectConverter.h"
#include "OnlineSubsystemClasses.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MenuPrincipalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


void AMenuPrincipalGameMode::CriaSalaHost(int32 NumeroJogador,int32 CenarioEscolhido,FString NomeSala)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInt = OnlineSubsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			// Configurações da sala, como nome, mapa, etc.
			SessionSettings.bIsLANMatch = false;
			SessionSettings.BuildUniqueId = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.bUsesStats = true;
			SessionSettings.bIsDedicated = true;
			SessionSettings.NumPublicConnections = NumeroJogador;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bAllowInvites = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = true;
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
			FNamedOnlineSession* DadosSessao = SessionInt->GetNamedSession(*NomeSala);
			FSala Dados;
			Dados.idSala = DadosSessao->GetSessionIdStr();
			Dados.NomeSala = NomeSala;
			Dados.MapaIndex = FString::FromInt(CenarioEscolhido);
			Dados.Cenario = "Fase" + FString::FromInt(CenarioEscolhido);
			
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			Dados.IP = "192.168.0.1";
			//Dados.IP = "PlayerController->GetNetConnection()->RemoteAddressToString()";

			Dados.Lan = UKismetStringLibrary::Conv_BoolToString(SessionSettings.bIsLANMatch);
			Dados.NumeroJogadoresAtivos = FString::FromInt(1);
			Dados.NumeroJogadoresTotais = FString::FromInt(NumeroJogador);
			Dados.ServidorDedicado = UKismetStringLibrary::Conv_BoolToString(SessionSettings.bIsDedicated);
			
			SalvaDadosSala(Dados);
		}
	}
}
void AMenuPrincipalGameMode::SalvaDadosSala(FSala DadosSala)
{
	UDevLopWarGameInstance* GameInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	FString Url = "http://localhost:8080/usuario/salvarSala";
	FString Verb = "POST";

	TSharedPtr<FJsonObject> JsonDados = MakeShareable(new FJsonObject);
	JsonDados->SetStringField("idSala", DadosSala.idSala);
	JsonDados->SetStringField("nomeSala", DadosSala.NomeSala);
	JsonDados->SetStringField("mapaIndex", DadosSala.MapaIndex);
	JsonDados->SetStringField("cenario", DadosSala.Cenario);
	JsonDados->SetStringField("ip", DadosSala.IP);
	JsonDados->SetStringField("lan", DadosSala.Lan);
	JsonDados->SetStringField("numeroJogadoresAtivos", DadosSala.NumeroJogadoresAtivos);
	JsonDados->SetStringField("numeroJogadoresTotais", DadosSala.NumeroJogadoresTotais);
	JsonDados->SetStringField("servidorDedicado", DadosSala.ServidorDedicado);

	FString Conteudo = "";
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Conteudo);
	FJsonSerializer::Serialize(JsonDados.ToSharedRef(), Writer);
	
	ChamadaHttp->EnviaRequisicaoHttpJsonHeader(Url, Verb, Conteudo, this, FName("EntrarLobbyCenario"),GameInstance->token);
}



void AMenuPrincipalGameMode::EntrarLobbyCenario(bool Conectou)
{
	if (Conectou)
	{
		GetWorld()->ServerTravel("/Game/Mapas/SalaEsperaPartida?listen");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"Falhou a criação da sala");
	}
}
void AMenuPrincipalGameMode::ProcuraDadosSala()
{
	UDevLopWarGameInstance* GameInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	FString Url = "http://localhost:8080/usuario/verDadosSalas";
	FString Verb = "GET";

	ChamadaHttp->EnviaRequisicaoHttpGetHeader(Url, Verb, this, FName("RetornaDadosSala"),GameInstance->token);
}
void AMenuPrincipalGameMode::RetornaDadosSala(FCallbackParametros CallbackParams)
{
	if (CallbackParams.conectou)
	{
		if (FJsonObjectConverter::JsonArrayStringToUStruct(CallbackParams.RespostaDados.ResponseContent, &GeraDados, 0, 0))
		{
			hudDetectada->OnFindSessionsComplete(true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Não achou nada");
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Falhou o json");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"Falhou na busca");
	}
}