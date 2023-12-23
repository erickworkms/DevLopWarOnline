//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevOpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ADevOpPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	APlayerController* JogadoresSala;
	UPROPERTY(Replicated)
	int32 IndexJogador;
	UPROPERTY(Replicated)
	ETime Time;
	
	
	UFUNCTION(BlueprintCallable)
	int32 GetNumZumbiesMortos();
	UFUNCTION(Reliable,Client)
	void SetNumZumbiesMortos(int32 NumZumbiesMortosSet);
	UFUNCTION(BlueprintCallable)
	int32 GetNumJogadoresMortos();
	UFUNCTION(Reliable,Client)
	void SetNumJogadoresMortos(int32 NumJogadoresMortosSet);
	UFUNCTION(BlueprintCallable)
	int32 GetNumMortes();
	UFUNCTION(Reliable,Client)
	void SetNumMortes(int32 NumMortesSet);
	UFUNCTION(BlueprintCallable)
	ETime GetTimeEscolhido();
	UFUNCTION(Reliable,Client)
	void SetTimeEscolhido(ETime TimeEscolhidoSet);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(ReplicatedUsing=SetNumZumbiesMortos)
	int32 NumZumbiesMortos;
	UPROPERTY(ReplicatedUsing=SetNumJogadoresMortos)
	int32 NumJogadoresMortos;
	UPROPERTY(ReplicatedUsing=SetNumMortes)
	int32 NumMortes;
	UPROPERTY(ReplicatedUsing=SetTimeEscolhido)
	ETime TimeEscolhido;
};
