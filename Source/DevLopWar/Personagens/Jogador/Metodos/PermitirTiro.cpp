//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::Permite_Tiro()
{
	if (PermiteTiro == false && Mirar == true && ArmaAquecida == false)
	{
		CriaProjetil();
		GetWorldTimerManager().SetTimer(ProjetilTemporizador, this, &AJogador_Base::Permite_Tiro, VelocidadeTiro, false);
		ArmaAquecimento -= VelocidadeTiro * 30;
		if (ArmaAquecimento <= 0.0f)
		{
			ArmaAquecida = true;
		}
	}
	else if (Mirar == false)
	{
		PermiteTiro = true;
	}
}
