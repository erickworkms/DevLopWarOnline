

#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::VerificaEscolhaPersonagem()
{
	switch (PersonagemNPC)
	{
	case Estagiario:
		VerificaMeshPersonagem(0);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Estagiario_Anim->GeneratedClass);
		break;
	case Pleno:
		VerificaMeshPersonagem(1);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Pleno_Anim->GeneratedClass);
		break;
	case Senior:
		VerificaMeshPersonagem(2);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Senior_Anim->GeneratedClass);
		break;
	case Chefe:
		VerificaMeshPersonagem(3);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Chefe_Anim->GeneratedClass);
		break;
	default:
		VerificaMeshPersonagem(0);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Estagiario_Anim->GeneratedClass);
		break;
	}
}
