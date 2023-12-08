//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWarGameInstance.h"

#include "Net/UnrealNetwork.h"


void UDevLopWarGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UDevLopWarGameInstance,ControleJogador);
	DOREPLIFETIME(UDevLopWarGameInstance,IndexJogador);
	DOREPLIFETIME(UDevLopWarGameInstance,Time);
}
