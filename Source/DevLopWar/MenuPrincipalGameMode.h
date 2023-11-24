// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineSessionSettings.h"
#include "Estruturas/Struct.h"
#include "Huds/BaseHudMenuPrincipal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuPrincipalGameMode.generated.h"

/**
 * 
 */
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
	void ProcuraSalaHost();
	UFUNCTION(BlueprintCallable)
	void DeslogarJogador();
	UFUNCTION(BlueprintCallable)
	void ProcuraSalaHostLista();
	UFUNCTION(BlueprintCallable)
	void ConectaSalaID(FName sessao,int32 idPesquisa);
	
	UFUNCTION()
	void OnFindSessionsComplete(bool Conectou);

	//UFUNCTION(BlueprintCallable)
	void ConectaSalaHost(const FOnlineSessionSearchResult& SearchResult);

	void HandleJoinSession(UNetConnection* Conexao);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void RetornaBuscar();

	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;
private:
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	TArray<FOnlineSessionSearchResult> FoundSessions; 
};
