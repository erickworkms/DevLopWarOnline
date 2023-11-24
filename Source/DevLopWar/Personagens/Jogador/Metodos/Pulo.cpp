#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::VerificaPulo_Pressionado()
{
	if (Estado == NoChaoAndando)
	{
		ResetaAcoes();
		Jump();
		Acao = Pular;
	}
}

void AJogador_Base::VerificaPulo_Solto()
{
}