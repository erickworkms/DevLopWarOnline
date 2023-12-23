//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWarGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UDevLopWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	APlayerController* ControleJogador;
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	int32 IndexJogador;
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	ETime Time;
	
	UPROPERTY(BlueprintReadWrite)
	FString token;

	UPROPERTY(BlueprintReadWrite)
	FString ip;
	
	UPROPERTY(BlueprintReadWrite)
	FString NomeJogador = "Server";

	UPROPERTY(BlueprintReadOnly)
	TArray<FSala> GeraDados;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	TArray<FInformacaoJogador> Jogadores;

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> JogadoresSala;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> JogadoresSalaNome;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	int32 TotalJogadores;
	
	FOnlineSessionSettings SessionSettings;
	IOnlineSessionPtr SessionInt;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
