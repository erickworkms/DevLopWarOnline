// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	TArray<FInformacaoJogador> Jogadores;

	UFUNCTION()
	float OnRep_TempoJogo();
	UFUNCTION()
	float OnRep_VidaTerritorio1();
	UFUNCTION()
	float OnRep_VidaTerritorio2();
	UFUNCTION()
	float OnRep_VidaTerritorio3();
	UFUNCTION()
	float OnRep_VidaTerritorio4();
	UFUNCTION()
	float OnRep_TimeVencedor();
private:
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
	ETime TimeVencedor = ETime::Clientes;
	
	UFUNCTION(BlueprintCallable)
	void AdicionaJogadorTime(const FString& NomeJogador,const ETime& Time);
	UFUNCTION(BlueprintCallable)
	void RemoveJogadorTime(const FString& NomeJogador);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
