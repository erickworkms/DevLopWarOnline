//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::AlterarNumZumbiesMortos_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]->PlayerState);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].NumZumbiesMortos++;
			PlayerState->SetNumZumbiesMortos(InformacaoGameplay[Index].NumZumbiesMortos);
		}
	}
}

void ADevLopWarGameMode::AlterarNumJogadoresMortos_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]->PlayerState);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].NumJogadoresMortos++;
			PlayerState->SetNumJogadoresMortos(InformacaoGameplay[Index].NumJogadoresMortos);
		}
	}
}

void ADevLopWarGameMode::AlterarNumMortes_Implementation(int32 Index)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerStateLocal = Cast<ADevOpPlayerState>(JogadoresSala[Index]->PlayerState);
		if (IsValid(PlayerStateLocal))
		{
			InformacaoGameplay[Index].NumMortes++;
			PlayerStateLocal->SetNumMortes(InformacaoGameplay[Index].NumMortes);
		}
	}
}

void ADevLopWarGameMode::AlterarTimeEscolhido_Implementation(int32 Index,ETime Time)
{
	if (IsValid(JogadoresSala[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(JogadoresSala[Index]);
		if (IsValid(PlayerState))
		{
			InformacaoGameplay[Index].TimeEscolhido = Time;
			PlayerState->SetTimeEscolhido(InformacaoGameplay[Index].TimeEscolhido);
		}
	}
}