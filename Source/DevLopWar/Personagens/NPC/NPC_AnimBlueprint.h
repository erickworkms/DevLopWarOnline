// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopWar/Personagens/Enums/Lista_Enums.h"
#include "NPC_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UNPC_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNPC_AnimBlueprint();
	
	FVector LocalArma;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Vida;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Velocidade;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoAcao> Acao = Nada;
	
	//Lista de funções	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	APawn* Personagem;
};
