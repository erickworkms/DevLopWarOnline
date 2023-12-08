//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWarGameMode.generated.h"

UCLASS(minimalapi)
class ADevLopWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ADevLopWarGameMode();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	TArray<FInformacaoJogador> Jogadores;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "times")
	TArray<FInformacaoJogadorGameplay> InformacaoGameplay;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<APlayerController*> JogadoresSala;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> JogadoresSalaNome;

	UPROPERTY(BlueprintReadOnly)
	TArray<FSala> GeraDados;

	FTimerHandle Contador;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AdicionaJogadorTime(const FString& NomeJogador,const ETime& Time);
	UFUNCTION(BlueprintCallable)
	void RemoveJogadorTime(const FString& NomeJogador);
	UFUNCTION(BlueprintCallable)
	void AcessaInformacoesTime(TArray<APlayerController*> ListaJogadores);
	
	UFUNCTION(Reliable,Server)
	void AlterarNumZumbiesMortos(int32 Index);
	UFUNCTION(Reliable,Server)
	void AlterarNumJogadoresMortos(int32 Index);
	UFUNCTION(Reliable,Server)
	void AlterarNumMortes(int32 Index);
	UFUNCTION(Reliable,Server)
	void AlterarTimeEscolhido(int32 Index,ETime Time);

	UFUNCTION(Reliable,Server)
	void DanoAtaqueProjetil(AActor* DonoProjetil,AActor* InimigoDetectado,AActor* Projetil);
private:
	UPROPERTY()
	float TempoJogo = 300;

	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
	
	UPROPERTY(Replicated)
	float VidaTerritorio1 = 100;
	UPROPERTY(Replicated)
	ETime VidaTerritorio1Dono = ETime::Nenhum;
	
	UPROPERTY(Replicated)
	float VidaTerritorio2 = 100;
	UPROPERTY(Replicated)
	ETime VidaTerritorio2Dono = ETime::Nenhum;
	
	UPROPERTY(Replicated)
	float VidaTerritorio3 = 100;
	UPROPERTY(Replicated)
	ETime VidaTerritorio3Dono = ETime::Nenhum;
	
	UPROPERTY(Replicated)
	float VidaTerritorio4 = 100;
	UPROPERTY(Replicated)
	ETime VidaTerritorio4Dono = ETime::Nenhum;
	
	UPROPERTY(Replicated)
	ETime TimeVencedor = ETime::Clientes;
	
	UPROPERTY()
	ADevLopWarGameStateBase* GameStateServer;
	UFUNCTION(Reliable,Server)
	void ContadorTempo();
};



