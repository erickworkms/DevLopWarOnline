//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "DevLopWar/Controles/GamePlayController.h"

void AGamePlayController::EscolhePersonagem_Implementation(TipoPersonagem PersonagemNPC)
{
	if (IsValid(GetPawn()) && HasAuthority())
	{
		Personagem = Cast<AJogador_Base>(GetPawn());
		if (IsValid(Personagem))
		{
			bShowMouseCursor = false;
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->VerificaEscolhaPersonagem();
			EscolhePersonagemCliente(PersonagemNPC);
		}
	}
}

void AGamePlayController::EscolhePersonagemCliente_Implementation(TipoPersonagem PersonagemNPC)
{
	if (IsValid(GetPawn()))
	{
		Personagem = Cast<AJogador_Base>(GetPawn());
		if (IsValid(Personagem))
		{
			bShowMouseCursor = false;
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->VerificaEscolhaPersonagem();
		}
	}
}