//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LoginGameMode.h"

#include "HttpModule.h"
#include "SocketSubsystem.h"
#include "Interfaces/IHttpResponse.h"
#include "GameFramework/HUD.h"
#include "Dom/JsonObject.h"
#include "DevLopWar/RequisicoesRede/RequisicaoHttp.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"

ALoginGameMode::ALoginGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudTelaLogin"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
}

void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (DefaultPlayerController)
	{
		DefaultPlayerController->bShowMouseCursor = true;
		DefaultPlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;
	}
	ChamadaHttp = NewObject<URequisicaoHttp>();
	GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	CapturaNumeroIP();
}

void ALoginGameMode::CriarUsuario(FDadosUsuario DadosUsuario)
{
	FString Url = "http://localhost:8080/usuario/criarLogin";
	FString Verb = "POST";

	TSharedPtr<FJsonObject> JsonDados = MakeShareable(new FJsonObject);
	JsonDados->SetStringField("nome", DadosUsuario.nome);
	JsonDados->SetStringField("dataNascimento", DadosUsuario.dataNascimento);
	JsonDados->SetStringField("email", DadosUsuario.email);
	JsonDados->SetStringField("usuario", DadosUsuario.usuario);
	JsonDados->SetStringField("senha", DadosUsuario.senha);
	
	FString Conteudo = "";
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Conteudo);
	FJsonSerializer::Serialize(JsonDados.ToSharedRef(), Writer);
	
	ChamadaHttp->EnviaRequisicaoHttpJson(Url, Verb, Conteudo, hudDetectada, FName("RetornoCriacaoLogin"));
}

void ALoginGameMode::ExecutaLogin(FString Usuario, FString senha)
{
	const FString Parametros = FString::Printf(TEXT("nome=%s&senha=%s"), *Usuario, *senha);

	FString Url = "http://localhost:8080/usuario/verlogin";
	FString Verb = "POST";

	GameInstance->NomeJogador = Usuario;
	ChamadaHttp->EnviaRequisicaoHttpParam(Url, Verb, Parametros, hudDetectada, FName("RetornoDadosLogin"));
}

void ALoginGameMode::EntraTelaInicial()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TelaInicial"));
}

void ALoginGameMode::CapturaNumeroIP()
{ // 
	// TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	// TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequestRef(HttpRequest);
	//
	// HttpRequest->SetVerb("GET");
	// HttpRequest->SetURL("https://httpbin.org/ip");
	// HttpRequest->OnProcessRequestComplete().BindUObject(this, &ALoginGameMode::RetornoCapturaNumeroIP);
	// HttpRequest->ProcessRequest();
	
	FOutputDeviceNull Out;
	bool bCanBindAll = false;
	TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(Out, bCanBindAll);
	if (LocalIP->IsValid())
	{
		GameInstance->ip = LocalIP->ToString(false);
		UE_LOG(LogTemp, Warning, TEXT("Endereço IP Local: %s"), *GameInstance->ip);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Falha ao obter o endereço IP local."));
	}
}
//
void ALoginGameMode::RetornoCapturaNumeroIP(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConectado)
{
	if (bConectado && Response.IsValid())
	{
		FString EnderecoIPExterno;
		TSharedPtr<FJsonObject> JsonObject;
		
		if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Response->GetContentAsString()), JsonObject))
		{
			if (JsonObject->TryGetStringField("origin", EnderecoIPExterno))
			{
				GameInstance->ip = EnderecoIPExterno;
			}
		}
	}
}
