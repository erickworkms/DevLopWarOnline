// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Estruturas/Struct.h"
#include "GameFramework/GameStateBase.h"
#include "DevLopWarGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ADevLopWarGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	ADevLopWarGameStateBase();

public:
	UPROPERTY(Replicated)
	float TempoJogo = 36000000;
	UPROPERTY(Replicated)
	float VidaTerritorio1 = 100;
	UPROPERTY(Replicated)
	float VidaTerritorio2 = 100;
	UPROPERTY(Replicated)
	float VidaTerritorio3 = 100;
	UPROPERTY(Replicated)
	float VidaTerritorio4 = 100;
	UPROPERTY(Replicated)
	FString TimeVencedor = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	TArray<FInformacaoJogador> Jogadores;

	UFUNCTION(BlueprintCallable)
	void AdicionaJogadorTime(const FString& NomeJogador,const ETime& Time);
	UFUNCTION(BlueprintCallable)
	void RemoveJogadorTime(const FString& NomeJogador);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
