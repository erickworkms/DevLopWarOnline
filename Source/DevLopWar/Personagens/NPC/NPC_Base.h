//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "ObjetivoNPC.h"
#include "Components/BoxComponent.h"
#include "DevLopWar/Personagens/Enums/Lista_Enums.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DevLopWar/Controles/GamePlayController.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "NPC_Base.generated.h"

UCLASS()
class DEVLOPWAR_API ANPC_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC_Base();

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Vida = 100;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Velocidade;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float VelocidadeMax = 500;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float DistanciaCombate = 150;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool PodeMovimentar = true;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<TipoIAEstado> IA_Comportamento;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DanoAtaque;
	UPROPERTY(Replicated,EditAnywhere,meta = (AllowPrivateAccess = "true"))
	AObjetivoNPC* LocalObjetivoPatrulha;
	
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	AActor* InimigoEncontrado;

	//Detecta controles e variaveis da IA
	UPROPERTY()
	UBlackboardComponent* VariaveisIA_BlackBoard;
	UPROPERTY()
	AAIController* ControleNPC;

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FString MeshPlayer;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FString AnimacaoPlayer;
	// UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	// UClass* NPC_Anim;
	
	void GerenciaEscolhaInimigoIA();
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(Reliable,Server)
	void DefinePadroesVel(float deltatime);
	
	void VerificaPadroes();

	UFUNCTION(Reliable,Server)
	void VerificaVida();
	
	UFUNCTION(Reliable,Server)
	void DefineEstadoAtual();

	UFUNCTION(Reliable,Server)
	void VerificaLocalPatrulha();
	
	UFUNCTION(Reliable,Server)
	void MoverPersonagemPatrulha(FVector LocalPatrulha);
	
	UFUNCTION(Reliable,Server)
	void VerificaMetodoComportamento();
	
	UFUNCTION(Reliable,Server)
	void GerenciaVisaoPersonagemIA();
public:
	UFUNCTION(Reliable,Server)
	void ContadorApagaNPC();

	UFUNCTION(Reliable,Server)
	void ApagaNPC();

	UFUNCTION(Reliable,Server)
	void ResetaNPC();

	UFUNCTION(Reliable,Server)
	void InicializaNPC();

	UFUNCTION(Reliable,NetMulticast)
	void InicializaAttachPersonagem();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(Acao == Atacar && InimigoDetectado != this)
		{
			AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
			ADevLopWarGameMode* DevGameMode = Cast<ADevLopWarGameMode>(GameMode);
			AJogador_Base* Jogador_Detectado = Cast<AJogador_Base>(InimigoDetectado);
			AObjetivoNPC* Territorio_Detectado = Cast<AObjetivoNPC>(InimigoDetectado);
			
			if (IsValid(Jogador_Detectado))
			{
				if (Jogador_Detectado->Vida > 0)
				{				
					Jogador_Detectado->Vida -= 10;
					if (Jogador_Detectado->Vida <= 0)
					{
						AGamePlayController* Controle = Cast<AGamePlayController>(Jogador_Detectado->GetController());
						if (IsValid(Controle))
						{
							FTimerHandle Contador;
							GetWorldTimerManager().SetTimer(Contador, Controle, &AGamePlayController::ReviveJogador, 5, false);
							
							if (IsValid(GameMode))
							{
								if (IsValid(DevGameMode))
								{
									int NumeroJogador = DevGameMode->RetornaIndexJogador(Controle);
									if (NumeroJogador != 100)
									{
										DevGameMode->AlterarNumMortes(NumeroJogador);
									}
								}
							}
						}
					}
				}
			}else if (IsValid(Territorio_Detectado) && IsValid(DevGameMode))
			{
				DevGameMode->AtualizaDanoTerritorioNpc(Territorio_Detectado);
				if (Territorio_Detectado->Vida <= 0)
				{
					TArray<AObjetivoNPC*> ListaNpcs;
					for (TActorIterator<AObjetivoNPC> It(GetWorld()); It; ++It)
					{
						if (It->TimeTerritorio != ETime::Clientes)
						{
							ListaNpcs.Add(*It);
						}
					}
					if (ListaNpcs.Num() > 0)
					{
						LocalObjetivoPatrulha = ListaNpcs[FMath::RandRange(0, ListaNpcs.Num() - 1)];
						MoverPersonagemPatrulha(LocalObjetivoPatrulha->GetActorLocation());
					}
				}
				
			}
		}
	}

	UFUNCTION()
	void FimDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		// ResetaSaidaColisao(InimigoDetectado);
	}
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};


