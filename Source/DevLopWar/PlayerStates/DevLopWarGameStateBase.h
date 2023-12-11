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
	ETime GetDonoTerritorio1();
	UFUNCTION(Reliable,Server)
	void SetDonoTerritorio1(ETime DonoTerritorio1Set);
	UFUNCTION(BlueprintCallable)
	bool GetBloqueioTerritorio1();
	UFUNCTION(Reliable,Server)
	void SetBloqueioTerritorio1(bool BloqueioTerritorio1Set);
	
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio2();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio2(float VidaTerritorio2Set);
	UFUNCTION(BlueprintCallable)
	ETime GetDonoTerritorio2();
	UFUNCTION(Reliable,Server)
	void SetDonoTerritorio2(ETime DonoTerritorio2Set);
	UFUNCTION(BlueprintCallable)
	bool GetBloqueioTerritorio2();
	UFUNCTION(Reliable,Server)
	void SetBloqueioTerritorio2(bool BloqueioTerritorio2Set);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio3();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio3(float VidaTerritorio3Set);
	UFUNCTION(BlueprintCallable)
	ETime GetDonoTerritorio3();
	UFUNCTION(Reliable,Server)
	void SetDonoTerritorio3(ETime DonoTerritorio3Set);
	UFUNCTION(BlueprintCallable)
	bool GetBloqueioTerritorio3();
	UFUNCTION(Reliable,Server)
	void SetBloqueioTerritorio3(bool BloqueioTerritorio3Set);
	
	UFUNCTION(BlueprintCallable)
	float GetVidaTerritorio4();
	UFUNCTION(Reliable,Server)
	void SetVidaTerritorio4(float VidaTerritorio4Set);
	UFUNCTION(BlueprintCallable)
	ETime GetDonoTerritorio4();
	UFUNCTION(Reliable,Server)
	void SetDonoTerritorio4(ETime DonoTerritorio4Set);
	UFUNCTION(BlueprintCallable)
	bool GetBloqueioTerritorio4();
	UFUNCTION(Reliable,Server)
	void SetBloqueioTerritorio4(bool BloqueioTerritorio4Set);

	UFUNCTION(BlueprintCallable)
	bool GetVerificaTerritorioConquistado(int IndexTerritorio,ETime TimeAtualSet);
	
	UFUNCTION(BlueprintCallable)
	ETime GetTimeVencedor();
	UFUNCTION(Reliable,Server)
	void SetTimeVencedor();

private:

	UPROPERTY(ReplicatedUsing=SetTempoJogo)
	float TempoJogo;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio1)
	float VidaTerritorio1;
	UPROPERTY(ReplicatedUsing=SetDonoTerritorio1)
	ETime DonoTerritorio1;
	UPROPERTY(ReplicatedUsing=SetBloqueioTerritorio1)
	bool BloqueioTerritorio1;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio2)
	float VidaTerritorio2;
	UPROPERTY(ReplicatedUsing=SetDonoTerritorio2)
	ETime DonoTerritorio2;
	UPROPERTY(ReplicatedUsing=SetBloqueioTerritorio2)
	bool BloqueioTerritorio2;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio3)
	float VidaTerritorio3;
	UPROPERTY(ReplicatedUsing=SetDonoTerritorio3)
	ETime DonoTerritorio3;
	UPROPERTY(ReplicatedUsing=SetBloqueioTerritorio3)
	bool BloqueioTerritorio3;
	
	UPROPERTY(ReplicatedUsing=SetVidaTerritorio4)
	float VidaTerritorio4;
	UPROPERTY(ReplicatedUsing=SetDonoTerritorio4)
	ETime DonoTerritorio4;
	UPROPERTY(ReplicatedUsing=SetBloqueioTerritorio4)
	bool BloqueioTerritorio4;
	
	UPROPERTY(ReplicatedUsing=SetTimeVencedor)
	ETime TimeVencedor = ETime::Nenhum;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
