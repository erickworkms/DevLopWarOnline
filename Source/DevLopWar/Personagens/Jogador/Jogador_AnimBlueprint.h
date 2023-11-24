// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopWar/Personagens/Enums/Lista_Enums.h"
#include "Jogador_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UJogador_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UJogador_AnimBlueprint();
	
	FVector LocalArma;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Vida;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Velocidade;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float AnguloCorpo = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float AnguloCameraX = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float AnguloCameraY = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Direcao = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float VelTempAnimacao = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	bool Mira;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoAcao> Acao = Nada;
	
	//Lista de funções
	UFUNCTION(CallInEditor, BlueprintCallable, Category=Animacao)
	void CalculaDirecao(APawn* PersonagemBase);
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	APawn* Personagem = NULL;
};
