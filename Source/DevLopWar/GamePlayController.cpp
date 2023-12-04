// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayController.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Net/UnrealNetwork.h"
#include "Personagens/Jogador/Jogador_Base.h"



void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	SetReplicates(true);
}

void AGamePlayController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePlayController,Personagem);
}



void AGamePlayController::CriaPersonagem_Implementation()
{
	UWorld* World = GetWorld();
	check(World);
	TArray<AActor*> PlayerStartEncontrados;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		PlayerStartEncontrados.Add(*It);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"iniciou personagens");
	APlayerStart* PontoEscolhido = nullptr;
	if (PlayerStartEncontrados.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"pontos encontrados");
		PontoEscolhido = Cast<APlayerStart>(
			PlayerStartEncontrados[FMath::RandRange(0, PlayerStartEncontrados.Num() - 1)]);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,PontoEscolhido->GetActorLocation().ToString());
	}
	if (PontoEscolhido)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"passou ponto escolhido");
		Personagem = GetWorld()->SpawnActorDeferred<AJogador_Base>(
			AJogador_Base::StaticClass(),
			FTransform(PontoEscolhido->GetActorRotation(),
			           PontoEscolhido->GetActorLocation()));
		if (Personagem)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"criou personagem");
			Personagem->FinishSpawning(FTransform(PontoEscolhido->GetActorRotation(),
			                                      PontoEscolhido->GetActorLocation()));
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,Personagem->GetName());
		bShowMouseCursor = false;
		SetPawn(Personagem);
		Possess(Personagem);
	}
}

void AGamePlayController::EscolhePersonagem_Implementation(TipoPersonagem PersonagemNPC)
{
	if (IsValid(GetPawn()))
	{
		Personagem = Cast<AJogador_Base>(GetPawn());
		if (IsValid(Personagem))
		{
			bShowMouseCursor = false;
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->VerificaEscolhaPersonagem();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"funcionou");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"falhou no personagem");
	}
}