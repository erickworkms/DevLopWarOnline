//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::AdicionaJogadorTime(const FString& NomeJogador, const ETime& Time)
{
	FInformacaoJogador dados;
	dados.Nome = NomeJogador;
	dados.Time = Time;
	Jogadores.Add(dados);
}

void ADevLopWarGameMode::RemoveJogadorTime(const FString& NomeJogador)
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