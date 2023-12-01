// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "GameFramework/HUD.h"
#include "BaseHudMenuPrincipal.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ABaseHudMenuPrincipal : public AHUD
{
	GENERATED_BODY()

	ABaseHudMenuPrincipal();
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFindSessionsComplete(bool bWasSuccessful);

	UFUNCTION(BlueprintImplementableEvent)
	void RetornoCriacaoLogin(bool Conectou,FHttpResponseData RespostasDados);

	UFUNCTION(BlueprintImplementableEvent)
	void RetornoDadosLogin(bool Conectou,FHttpResponseData RespostasDados);
	
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveJogador(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void EnviaMensagemChat(const FString& mensagem);

	UFUNCTION(BlueprintImplementableEvent)
	void AdicionaHudSalas();
};
