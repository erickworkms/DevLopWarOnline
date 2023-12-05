//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"


void AJogador_Base::DefinePadroesVel(float valor)
{
	if (Mirar == true)
	{
		VelocidadeMax = 300;
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0, RotacaoMira,
													0));
		if (PermiteTiro == true && ArmaAquecida)
		{
			ArmaAquecimento += 1;
			if (ArmaAquecimento >= 99)
			{
				ArmaAquecida = false;
			}
		}
	}
	else
	{
		if (ArmaAquecida)
		{
			ArmaAquecimento += 1;
			if (ArmaAquecimento >= 99)
			{
				ArmaAquecida = false;
			}
		}
		VelocidadeMax = 600;
	}
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	PersonagemSeMovimenta = (GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y) > 0;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
	                              Velocidade, valor, 10.f);

	ApontamentoZControle = FMath::FInterpTo(ApontamentoZControle,
	                                        GetCharacterMovement()->GetLastUpdateVelocity().Z, valor, 10.f);
	if (Vida <= 0.0f)
	{
		Acao = Morto;
	}
}