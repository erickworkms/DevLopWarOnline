//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LoginGameMode.h"
#include "GameFramework/HUD.h"
#include "Dom/JsonObject.h"
#include "DevLopWar/RequisicoesRede/RequisicaoHttp.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "Kismet/GameplayStatics.h"

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
