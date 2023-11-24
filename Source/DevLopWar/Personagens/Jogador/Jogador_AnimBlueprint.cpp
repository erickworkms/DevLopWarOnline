// Fill out your copyright notice in the Description page of Project Settings.

#include "Jogador_AnimBlueprint.h"
#include "Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetStringLibrary.h"


void UJogador_AnimBlueprint::CalculaDirecao(APawn* PersonagemBase)
{
	AJogador_Base* PersonagemReferencia = Cast<AJogador_Base>(PersonagemBase);
	Direcao = CalculateDirection(Personagem->GetVelocity(), Personagem->GetActorRotation());

	if (Velocidade > 500)
	{
		VelTempAnimacao = FMath::Clamp(Velocidade /
									   FMath::Clamp(PersonagemBase->GetMovementComponent()->GetMaxSpeed(),
													0.0f, PersonagemReferencia->VelocidadeMax), 1.f,
									   5.f);
	}
	else
	{
		VelTempAnimacao = 1;
	}
}

UJogador_AnimBlueprint::UJogador_AnimBlueprint()
{
	Vida = 100.f;
	Velocidade = 0.f;
}

void UJogador_AnimBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Personagem = TryGetPawnOwner();
}

void UJogador_AnimBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Personagem)
	{
		return;
	}
	if (Personagem->IsA(AJogador_Base::StaticClass()))
	{
		AJogador_Base* PersonagemReferencia = Cast<AJogador_Base>(Personagem);
		
		if (PersonagemReferencia)
		{
			CalculaDirecao(PersonagemReferencia);

			Vida = PersonagemReferencia->Vida;
			Velocidade = PersonagemReferencia->Velocidade;
			AnguloCorpo = PersonagemReferencia->AnguloCorpo;
			AnguloCameraX = PersonagemReferencia->AnguloCameraX;
			AnguloCameraY = PersonagemReferencia->AnguloCameraY;
			Direcao = PersonagemReferencia->Direcao;
			VelTempAnimacao = PersonagemReferencia->VelTempAnimacao;
	
			Mira = PersonagemReferencia->Mirar;

			Estado = PersonagemReferencia->Estado;
			Acao = PersonagemReferencia->Acao;
		}
	}
}


