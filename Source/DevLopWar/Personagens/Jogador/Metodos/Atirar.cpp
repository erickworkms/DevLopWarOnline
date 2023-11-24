#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::Atirar_Pressionado()
{
	if (PermiteTiro == true && ArmaAquecida == false)
	{
		PermiteTiro = false;
		CriaProjetil();
		GetWorldTimerManager().SetTimer(ProjetilTemporizador, this, &AJogador_Base::Permite_Tiro, VelocidadeTiro, false);
		ArmaAquecimento -= VelocidadeTiro * 30;
		if (ArmaAquecimento <= 0.0f)
		{
			ArmaAquecida = true;
		}
	}
}

void AJogador_Base::Atirar_Solto()
{
	PermiteTiro = true;
}

void AJogador_Base::AtivarMira_Pressionado()
{
	AtivarMira_PressionadoServidor();
	if (!Mirar)
	{
		FRotator CameraRotacaoInicio = CameraPrincipal->GetComponentRotation() - FRotator::ZeroRotator;
		RotacaoMira = GetCamera()->GetComponentRotation().Yaw;
	
		AnguloCameraX = 0;
		AnguloCameraY = 0;

		GetController()->SetControlRotation(
				FRotator(0, CameraRotacaoInicio.Yaw, 0)
			);
		
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0,RotacaoMira,
															0));
	
		SpringArm->TargetArmLength = 70.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 25), FRotator(0, 0, 0));
		CameraPrincipal->SetRelativeLocationAndRotation(FVector(0, 50, 0), FRotator(0, 0, 0));
		LocalReferenciaCamera->SetRelativeLocation(FVector(-320, 0, -30));
	}
	Mirar = true;
}

void AJogador_Base::AtivarMira_Solto()
{
	AtivarMira_SoltoServidor();
	if (Mirar)
	{
		SpringArm->TargetArmLength = 400.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		CameraPrincipal->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		AnguloCameraX = 0;
		AnguloCameraY = 0;
		LocalReferenciaCamera->SetRelativeLocation(FVector(0, 0, 0));
		//FInterp da camera e FInterp do location e rotation, FInterp do spring arm lenght
	}
	Mirar = false;
}

void AJogador_Base::AtivarMira_PressionadoServidor_Implementation()
{
	if (!Mirar)
	{
		FRotator CameraRotacaoInicio = CameraPrincipal->GetComponentRotation() - FRotator::ZeroRotator;
		RotacaoMira = GetCamera()->GetComponentRotation().Yaw;
		
		AnguloCameraX = 0;
		AnguloCameraY = 0;
		
		GetController()->SetControlRotation(
							FRotator(0, CameraRotacaoInicio.Yaw, 0)
						);
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0, RotacaoMira,
															0));
	
		SpringArm->TargetArmLength = 70.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 25), FRotator(0, 0, 0));
		CameraPrincipal->SetRelativeLocationAndRotation(FVector(0, 50, 0), FRotator(0, 0, 0));
		LocalReferenciaCamera->SetRelativeLocation(FVector(-320, 0, -30));
	}
	Mirar = true;
}

void AJogador_Base::AtivarMira_SoltoServidor_Implementation()
{
	if (Mirar)
	{
		SpringArm->TargetArmLength = 400.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		CameraPrincipal->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		AnguloCameraX = 0;
		AnguloCameraY = 0;
		LocalReferenciaCamera->SetRelativeLocation(FVector(0, 0, 0));
		//FInterp da camera e FInterp do location e rotation, FInterp do spring arm lenght
	}
	Mirar = false;
}
