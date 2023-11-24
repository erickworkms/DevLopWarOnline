// Fill out your copyright notice in the Description page of Project Settings.


#include "Projetil.h"

#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "DevLopWar/Personagens/NPC/NPC_Base.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AProjetil::AProjetil()
{
}

// Called when the game starts or when spawned
void AProjetil::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjetil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjetil::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjetil, DonoProjetil);
	DOREPLIFETIME(AProjetil, Projetil);
	DOREPLIFETIME(AProjetil, ProjetilMesh);
}

void AProjetil::DanoAtaqueProjetil_Implementation(AActor* InimigoDetectado)
{
	AJogador_Base* Jogador_Detectado = Cast<AJogador_Base>(InimigoDetectado);
	AJogador_Base* Inimigo = Cast<AJogador_Base>(DonoProjetil);
	ANPC_Base* NPC_Detectado = Cast<ANPC_Base>(InimigoDetectado);

	if (IsValid(Jogador_Detectado))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
												 InimigoDetectado->GetName() + "bala" + GetName());
		Jogador_Detectado->Vida -= Inimigo->QuantidadeDano;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
										 FString::SanitizeFloat(Jogador_Detectado->Vida) + "vida" + GetName());

		Destroy();
	}
	if (IsValid(NPC_Detectado))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
												 InimigoDetectado->GetName() + "bala" + GetName());
		NPC_Detectado->Vida -= 10;
		Destroy();
	}
	else if (InimigoDetectado != DonoProjetil)
	{
		Destroy();
	}

}
