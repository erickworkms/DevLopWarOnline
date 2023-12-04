// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Personagens/Jogador/Jogador_Base.h"
#include "GamePlayController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API AGamePlayController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void CriaPersonagem();

	UFUNCTION(BlueprintCallable,Reliable,Server)
	void EscolhePersonagem(TipoPersonagem PersonagemNPC);

	UPROPERTY(BlueprintReadWrite,Replicated)
	AJogador_Base* Personagem;
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
