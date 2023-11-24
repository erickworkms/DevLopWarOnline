// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "GameFramework/GameModeBase.h"
#include "Huds/BaseHudMenuPrincipal.h"
#include "RequisicoesRede/RequisicaoHttp.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALoginGameMode();

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	URequisicaoHttp* ChamadaHttp;
	
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;
private:
	UFUNCTION(BlueprintCallable)
	void CriarUsuario(FDadosUsuario DadosUsuario);
	UFUNCTION(BlueprintCallable)
	void ExecutaLogin(FString Usuario,FString senha);
	UFUNCTION(BlueprintCallable)
	void EntraTelaInicial();
};
