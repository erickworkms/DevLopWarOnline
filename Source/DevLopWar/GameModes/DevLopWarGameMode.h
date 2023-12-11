//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controles/GamePlayController.h"
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

	FTimerHandle ReviverContador;

	virtual void BeginPlay() override;

	virtual void Logout(AController* Exiting) override;

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

	UFUNCTION(Reliable,Server)
	void CriaInformacoesJogadorServer(AGamePlayController* Controle,FInformacaoJogadorGameplay InformacaoGameplayLocal,int IndexJogador);

	UFUNCTION(Reliable,Server)
	void ReativaPontosObjetivo(int IndexObjetivo,bool EstadoBloqueio);

	UFUNCTION(BlueprintCallable,Reliable,Server)
	void RetornaLobby();

private:
	UPROPERTY()
	float TempoJogo = 50;

	UPROPERTY()
	bool JogoFinalizado = false;

	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
		
	UPROPERTY()
	ADevLopWarGameStateBase* GameStateServer;

	UFUNCTION(BlueprintCallable)
	void DetectaPontosObjetivo();
		
	UFUNCTION(Reliable,Server)
	void ContadorTempo();

	
};



