// Fill out your copyright notice in the Description page of Project Settings.

#include "DevLopWarGameStateBase.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Net/UnrealNetwork.h"

ADevLopWarGameStateBase::ADevLopWarGameStateBase()
{
	Jogadores.SetNum(8);
}

void ADevLopWarGameStateBase::AdicionaJogadorTime(const FString& NomeJogador, const ETime& Time)
{
	FInformacaoJogador dados;
	dados.Nome = NomeJogador;
	dados.Time = Time;
	Jogadores.Add(dados);
}

void ADevLopWarGameStateBase::RemoveJogadorTime(const FString& NomeJogador)
{
	for (int32 i = 0; i < Jogadores.Num(); ++i)
	{
		if (Jogadores[i].Nome.Equals(NomeJogador, ESearchCase::IgnoreCase))
		{
			Jogadores.RemoveAt(i);
		break;
		}
	}
	
}

void ADevLopWarGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevLopWarGameStateBase,TempoJogo);
	DOREPLIFETIME(ADevLopWarGameStateBase,VidaTerritorio1);
	DOREPLIFETIME(ADevLopWarGameStateBase,VidaTerritorio2);
	DOREPLIFETIME(ADevLopWarGameStateBase,VidaTerritorio3);
	DOREPLIFETIME(ADevLopWarGameStateBase,VidaTerritorio4);
	DOREPLIFETIME(ADevLopWarGameStateBase,TimeVencedor);
	DOREPLIFETIME(ADevLopWarGameStateBase,Jogadores);
}
