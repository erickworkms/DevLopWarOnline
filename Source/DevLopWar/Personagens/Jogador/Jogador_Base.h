// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "DevLopWar/Personagens/Enums/Lista_Enums.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Jogador_Base.generated.h"

UCLASS()
class DEVLOPWAR_API AJogador_Base : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraPrincipal;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Arma;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LocalReferenciaCamera;

public:
	// Sets default values for this character's properties
	AJogador_Base();
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FTimerHandle ProjetilTemporizador;

	TArray<FString> MeshesPlayer;
	TArray<FString> AnimacaoPlayer;
	FString CaminhoArma;

	UPROPERTY(BlueprintReadOnly,Replicated,Category="Variaveis")
	float Vida = 100;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Velocidade;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float AnguloCorpo;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float AnguloCameraX;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float AnguloCameraY;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Direcao;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float VelTempAnimacao;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float ApontamentoZControle = 0.f;
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float VelocidadeTiro = 0.05f;
	UPROPERTY(BlueprintReadOnly,Replicated,Category="Variaveis")
	float ArmaAquecimento = 100.0f;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float QuantidadeDano = 0.0f;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float VelocidadeMax = 1000;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float RotacaoMira;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(Replicated,EditAnywhere, Category="Personagem")
	TEnumAsByte<TipoPersonagem> PersonagemNPC = Senior;

	UAnimBlueprint* Estagiario_Anim;
	UAnimBlueprint* Pleno_Anim;
	UAnimBlueprint* Senior_Anim;
	UAnimBlueprint* Chefe_Anim;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool BloqueiaContador = true;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool PersonagemSeMovimenta;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool Mirar = false;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool PermiteTiro = true;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool ArmaAquecida = false;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FVector LocalSocketArma;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FRotator RotacaoSocketArma;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Botões sensíveis, direcional
	void MoverFrente(float valor);
	
	void MoverLado(float valor);

	void VirarCameraFrente(float valor);

	void VirarCameraLado(float valor);
	
	UFUNCTION(Reliable,Server)
	void VirarCameraFrenteServidor(float valor);
	UFUNCTION(Reliable,Server)
	void VirarCameraLadoServidor(float valor);

	void DefinePadroesVel(float valor);

	//Botões apertados
	void VerificaPulo_Pressionado();
	void VerificaPulo_Solto();
	void Atirar_Pressionado();
	void Atirar_Solto();
	
	void AtivarMira_Pressionado();
	void AtivarMira_Solto();

	UFUNCTION(Reliable,Server)
	void AtivarMira_PressionadoServidor();
	UFUNCTION(Reliable,Server)
	void AtivarMira_SoltoServidor();
	
	void Interagir_Pressionado();
	void Interagir_Solto();
	void Permite_Tiro();

	//Metodos
	void DefinePadroes();
	void ResetaAcoes();

	void DefineEstadoAtual();
	void CriaCameraConfig();
	void CriaPersonagemConfig();
	void CriaProjetil();
	UFUNCTION(Reliable,Server)
	void CriaProjetilServidor(FVector Local,FRotator Rotacao);
	void VerificaEscolhaPersonagem();
	void VerificaMeshPersonagem(float Index);

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }

	FORCEINLINE class UCameraComponent* GetCamera() const { return CameraPrincipal; }
};
