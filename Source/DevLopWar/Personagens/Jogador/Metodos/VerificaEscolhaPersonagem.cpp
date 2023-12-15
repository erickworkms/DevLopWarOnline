//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"


void AJogador_Base::VerificaEscolhaPersonagem()
{
	if(MeshesPlayer.Num() >= 4 && AnimacaoPlayer.Num() >=4)
	{
		switch (PersonagemNPC)
		{
		case Estagiario:
			VerificaMeshPersonagem(0);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Estagiario_Anim);
			break;
		case Pleno:
			VerificaMeshPersonagem(1);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Pleno_Anim);
			break;
		case Senior:
			VerificaMeshPersonagem(2);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Senior_Anim);
			break;
		case Chefe:
			VerificaMeshPersonagem(3);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Chefe_Anim);
			break;
		default:
			VerificaMeshPersonagem(0);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Estagiario_Anim);
			break;
		}
	}
}
void AJogador_Base::CarregarAssetsPersonagem()
{
	
}