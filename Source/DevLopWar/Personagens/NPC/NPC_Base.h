//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "ObjetivoNPC.h"
#include "Components/BoxComponent.h"
#include "DevLopWar/Personagens/Enums/Lista_Enums.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
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
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(Acao == Atacar && InimigoDetectado != this)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
							  "Nome do inimigo "+InimigoDetectado->GetName());
	
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
