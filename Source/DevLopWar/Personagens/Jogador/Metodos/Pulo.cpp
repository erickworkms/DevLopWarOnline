//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::VerificaPulo_Pressionado()
{
	if (Estado == NoChaoAndando)
	{
		Jump();
		Acao = Pular;
	}
}

void AJogador_Base::VerificaPulo_Solto()
{
}