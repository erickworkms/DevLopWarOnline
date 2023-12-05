//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/PlayerController.h"
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

	UFUNCTION(BlueprintCallable,Reliable,Client)
	void EscolhePersonagemCliente(TipoPersonagem PersonagemNPC);

	UPROPERTY(BlueprintReadWrite,Replicated)
	AJogador_Base* Personagem;
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
