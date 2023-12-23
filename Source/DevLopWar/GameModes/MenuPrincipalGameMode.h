//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineSessionSettings.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Containers/UnrealString.h" 
#include "DevLopWar/RequisicoesRede/RequisicaoHttp.h"
#include "Engine/Engine.h"
#include "MenuPrincipalGameMode.generated.h"

UCLASS()
class DEVLOPWAR_API AMenuPrincipalGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMenuPrincipalGameMode();
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FSala> GeraDados;
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CriaSalaHost(int32 NumeroJogador,int32 CenarioEscolhido,FString NomeSala);
	UFUNCTION(BlueprintCallable)
	void ProcuraSalaHost(FString IPEscolhido, int PortaEscolhida,bool Lan);
	UFUNCTION(BlueprintCallable)
	void DeslogarJogador();
	
	UFUNCTION(BlueprintCallable)
	void ProcuraSalaHostLista(FString EnderecoIP,int Porta,bool Lan);
	UFUNCTION(BlueprintCallable)
	void VerificaResultadosBuscaSalas(bool Conectou);
	// UFUNCTION(BlueprintCallable)
	// void VerificarDadosSalaID(bool Conectou);
	
	UFUNCTION(BlueprintCallable)
	void ConectaSalaID(FName sessao,int32 idPesquisa);
	UFUNCTION(BlueprintCallable)
	void SalvaDadosSala(FSala DadosSala);
	UFUNCTION()
	void DeletaDadosSala(FString usuarioCriador);
	UFUNCTION()
	void RetornaDeleteDadosSala(FCallbackParametros CallbackParams);
	
	
	UFUNCTION(BlueprintCallable)
	void ProcuraDadosSala();
	UFUNCTION(BlueprintCallable)
	void RetornaDadosSala(FCallbackParametros CallbackParams);
	UFUNCTION(BlueprintCallable)
	void EntrarLobbyCenario(bool Conectou);
	
	UFUNCTION()
	void OnFindSessionsComplete(bool Conectou);

	UPROPERTY(BlueprintReadOnly)
	URequisicaoHttp* ChamadaHttp;
	
	void ConectaSalaHost(const FOnlineSessionSearchResult& SearchResult);

	void HandleJoinSession(FName SessionName);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	FString GetStringFromConnectionState(ESocketConnectionState ConnectionState);
		
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;

	FSocket* UDPSocket;
	
	const TCHAR* EnderecoIP ;
	FString EnderecoIPBruto ;
	
	int Porta = 7777;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
	
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	TArray<FOnlineSessionSearchResult> FoundSessions;
	FOnlineSessionSettings SessionSettings;
};
