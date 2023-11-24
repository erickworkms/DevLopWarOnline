// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Huds/BaseHudMenuPrincipal.h"
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
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> JogadoresSala;
	
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;
	
	virtual void BeginPlay() override;

	FOnPlayerJoinedDelegate OnPlayerJoined;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void IniciaPartida();

	UFUNCTION(BlueprintCallable)
	void VerEntradaLogin();
	
	UFUNCTION(BlueprintCallable)
	void EnviarMensagemChat(FString mensagem);
};
