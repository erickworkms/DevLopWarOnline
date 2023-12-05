//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LobbyGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinedDelegate, APlayerController*, NovoJogador);

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALobbyGameMode();

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<APlayerController*> JogadoresSala;

	UPROPERTY(Replicated,BlueprintReadOnly)
	TArray<FString> JogadoresSalaNome;

	UPROPERTY(BlueprintReadOnly)
	TArray<FSala> GeraDados;

	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;

	virtual void BeginPlay() override;

	FOnPlayerJoinedDelegate OnPlayerJoined;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void IniciaPartida();

	UFUNCTION(BlueprintCallable)
	void VerEntradaLogin();

	UFUNCTION()
	void HandlePlayerJoined(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EnviarMensagemChat(const FString& mensagem);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void DesconectaCliente(APlayerController* PlayerController, int32 Id);

	UFUNCTION(BlueprintCallable)
	void ExcluirSala();
	
	UFUNCTION()
	void TimerHud();

	UPROPERTY()
	int ValorIndexUsuarioAtraso=0;

	FTimerHandle Contador;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	UPROPERTY()
	UDevLopWarGameInstance* SeuGameInstance;
};
