#include "GameFramework/CharacterMovementComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::DefineEstadoAtual()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		Estado = Caindo;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		Estado = Voando;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		Estado = NoChaoAndando;
	}
	else
	{
		Estado = NoChaoAndando;
	}
}
