// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Huds/BaseHudMenuPrincipal.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyController();
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void EnviarMensagemServer(const FString& nome,const FString& mensagem);

	UFUNCTION(Reliable,Client)
	void EnviarMensagemCliente(const FString& nome,const FString& mensagem);
	
	UFUNCTION(Reliable,Client)
	void VerEntradaLogin(const TArray<FString>& JogadoresSalaNome);

	UPROPERTY(Replicated,BlueprintReadWrite)
	ABaseHudMenuPrincipal* HudChat;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

};
