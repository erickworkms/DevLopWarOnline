//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "Projetil.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Net/UnrealNetwork.h"

// Sets default values
AProjetil::AProjetil()
{
}


void AProjetil::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjetil, DonoProjetil);
	DOREPLIFETIME(AProjetil, Projetil);
	DOREPLIFETIME(AProjetil, ProjetilMesh);
}

void AProjetil::DanoAtaqueProjetil_Implementation(AActor* InimigoDetectado)
{
	AGameModeBase* GameModeEncontrado = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeEncontrado);
	GameMode->DanoAtaqueProjetil(DonoProjetil,InimigoDetectado,this);
}
