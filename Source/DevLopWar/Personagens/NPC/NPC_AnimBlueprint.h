//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
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
	UPROPERTY()
	APawn* Personagem;
};
