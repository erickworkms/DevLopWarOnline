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
	
	UFUNCTION(BlueprintCallable)
	float GetTempoJogo();
	UFUNCTION(Reliable,Server)
	void SetTempoJogo(float TempoJogoSet);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio1();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio1(float VidaTerritorio1Set);
	UFUNCTION(BlueprintCallable)
	ETime GetVidaTerritorio1Dono();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio1Dono(ETime VidaTerritorio1DonoSet);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio2();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio2(float VidaTerritorio2Set);
	UFUNCTION(BlueprintCallable)
	ETime GetVidaTerritorio2Dono();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio2Dono(ETime VidaTerritorio2DonoSet);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio3();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio3(float VidaTerritorio3Set);
	UFUNCTION(BlueprintCallable)
	ETime GetVidaTerritorio3Dono();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio3Dono(ETime VidaTerritorio3DonoSet);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio4();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio4(float VidaTerritorio4Set);
	UFUNCTION(BlueprintCallable)
	ETime GetVidaTerritorio4Dono();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio4Dono(ETime VidaTerritorio4DonoSet);
	
	UFUNCTION(BlueprintCallable)
	ETime GetTimeVencedor();
	UFUNCTION(Reliable,Server)
	void SetTimeVencedor(ETime TimeVencedorSet);

private:

	UPROPERTY(ReplicatedUsing=SetTempoJogo)
	float TempoJogo;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio1)
	float VidaTerritorio1;
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio1Dono)
	ETime VidaTerritorio1Dono;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio2)
	float VidaTerritorio2;
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio2Dono)
	ETime VidaTerritorio2Dono;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio3)
	float VidaTerritorio3;
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio3Dono)
	ETime VidaTerritorio3Dono;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio4)
	float VidaTerritorio4;
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio4Dono)
	ETime VidaTerritorio4Dono;
	
	UPROPERTY(ReplicatedUsing=SetTimeVencedor)
	ETime TimeVencedor = ETime::Clientes;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
