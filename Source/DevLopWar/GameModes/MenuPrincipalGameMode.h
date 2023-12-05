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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	UPROPERTY()
	UDevLopWarGameInstance* SeuGameInstance;
	
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	TArray<FOnlineSessionSearchResult> FoundSessions;
	FOnlineSessionSettings SessionSettings;
};
