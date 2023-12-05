//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "NPC_AnimBlueprint.h"
#include "NPC_Base.h"

UNPC_AnimBlueprint::UNPC_AnimBlueprint()
{
	Velocidade = 0.f;
}

void UNPC_AnimBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Personagem = TryGetPawnOwner();
}

void UNPC_AnimBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Personagem)
	{
		return;
	}
	if (Personagem->IsA(ANPC_Base::StaticClass()))
	{
		ANPC_Base* PersonagemReferencia = Cast<ANPC_Base>(Personagem);
		
		if (PersonagemReferencia)
		{
			Vida = PersonagemReferencia->Vida;
			Velocidade = PersonagemReferencia->Velocidade;
			Estado = PersonagemReferencia->Estado;
			Acao = PersonagemReferencia->Acao;
		}
	}
}
