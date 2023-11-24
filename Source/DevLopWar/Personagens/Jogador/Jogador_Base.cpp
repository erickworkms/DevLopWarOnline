// Fill out your copyright notice in the Description page of Project Settings.


#include "Jogador_Base.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AJogador_Base::AJogador_Base()
{
	CriaPersonagemConfig();
	CriaCameraConfig();
}

// Called when the game starts or when spawned
void AJogador_Base::BeginPlay()
{
	Super::BeginPlay();
	DefinePadroes();
	VerificaEscolhaPersonagem();
}

// Called every frame
void AJogador_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DefineEstadoAtual();
	DefinePadroesVel(DeltaTime);
	// FRotator CameraRotacaoInicio = CameraPrincipal->GetSocketRotation("none") - FRotator::ZeroRotator;
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
	// 										 FString::SanitizeFloat(CameraRotacaoInicio.Yaw) + "Angulo x" + GetName());
}

// Called to bind functionality to input
void AJogador_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoverFrente"), this, &AJogador_Base::MoverFrente);
	PlayerInputComponent->BindAxis(TEXT("MoverLado"), this, &AJogador_Base::MoverLado);

	PlayerInputComponent->BindAxis(TEXT("VirarCameraFrente"), this, &AJogador_Base::VirarCameraFrente);
	PlayerInputComponent->BindAxis(TEXT("VirarCameraLado"), this, &AJogador_Base::VirarCameraLado);

	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Pressed, this, &AJogador_Base::VerificaPulo_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Released, this, &AJogador_Base::VerificaPulo_Solto);

	PlayerInputComponent->
		BindAction(TEXT("Atirar"), IE_Pressed, this, &AJogador_Base::Atirar_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Atirar"), IE_Released, this, &AJogador_Base::Atirar_Solto);

	PlayerInputComponent->BindAction(TEXT("AtivarMira"), IE_Pressed, this, &AJogador_Base::AtivarMira_Pressionado);
	PlayerInputComponent->BindAction(TEXT("AtivarMira"), IE_Released, this, &AJogador_Base::AtivarMira_Solto);

	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Pressed, this,
	                                 &AJogador_Base::Interagir_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Released, this,
	                                 &AJogador_Base::Interagir_Solto);
}

void AJogador_Base::ResetaAcoes()
{
}

void AJogador_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	VerificaEscolhaPersonagem();
}

void AJogador_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AJogador_Base, Vida);
	DOREPLIFETIME(AJogador_Base, Velocidade);
	DOREPLIFETIME(AJogador_Base, AnguloCorpo);
	DOREPLIFETIME(AJogador_Base, AnguloCameraX);
	DOREPLIFETIME(AJogador_Base, AnguloCameraY);
	DOREPLIFETIME(AJogador_Base, VelocidadeTiro);
	DOREPLIFETIME(AJogador_Base, ArmaAquecimento);
	DOREPLIFETIME(AJogador_Base, QuantidadeDano);
	DOREPLIFETIME(AJogador_Base, VelocidadeTiro);
	DOREPLIFETIME(AJogador_Base, VelocidadeMax);
	DOREPLIFETIME(AJogador_Base, VelTempAnimacao);
	DOREPLIFETIME(AJogador_Base, RotacaoMira);

	DOREPLIFETIME(AJogador_Base, Mirar);
	DOREPLIFETIME(AJogador_Base, BloqueiaContador);
	DOREPLIFETIME(AJogador_Base, PersonagemSeMovimenta);
	DOREPLIFETIME(AJogador_Base, PermiteTiro);
	DOREPLIFETIME(AJogador_Base, ArmaAquecida);
	
	DOREPLIFETIME(AJogador_Base, Estado);
	DOREPLIFETIME(AJogador_Base, Acao);
	DOREPLIFETIME(AJogador_Base, PersonagemNPC);
	DOREPLIFETIME(AJogador_Base, Arma);
	DOREPLIFETIME(AJogador_Base, LocalReferenciaCamera);
	DOREPLIFETIME(AJogador_Base, ProjetilTemporizador);
	DOREPLIFETIME(AJogador_Base, CameraPrincipal);
	DOREPLIFETIME(AJogador_Base, SpringArm);
	DOREPLIFETIME(AJogador_Base, LocalSocketArma);
	DOREPLIFETIME(AJogador_Base, RotacaoSocketArma);
}
