//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "DevOpPlayerState.h"

#include "Net/UnrealNetwork.h"

void ADevOpPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevOpPlayerState,NumZumbiesMortos);
	DOREPLIFETIME(ADevOpPlayerState,NumJogadoresMortos);
	DOREPLIFETIME(ADevOpPlayerState,NumMortes);
	DOREPLIFETIME(ADevOpPlayerState,TimeEscolhido);
	DOREPLIFETIME(ADevOpPlayerState,JogadoresSala);
	DOREPLIFETIME(ADevOpPlayerState,IndexJogador);
	DOREPLIFETIME(ADevOpPlayerState,Time);
}

int32 ADevOpPlayerState::GetNumZumbiesMortos() 
{
	return NumZumbiesMortos;
}

void ADevOpPlayerState::SetNumZumbiesMortos_Implementation(int32 NumZumbiesMortosSet)
{
	NumZumbiesMortos = NumZumbiesMortosSet;
}

int32 ADevOpPlayerState::GetNumJogadoresMortos() 
{
	return NumJogadoresMortos;
}

void ADevOpPlayerState::SetNumJogadoresMortos_Implementation(int32 NumJogadoresMortosSet)
{
	NumJogadoresMortos = NumJogadoresMortosSet;
}

int32 ADevOpPlayerState::GetNumMortes() 
{
	return NumMortes;
}

void ADevOpPlayerState::SetNumMortes_Implementation(int32 NumMortesSet)
{
	NumMortes = NumMortesSet;
}

ETime ADevOpPlayerState::GetTimeEscolhido() 
{
	return TimeEscolhido;
}

void ADevOpPlayerState::SetTimeEscolhido_Implementation(ETime TimeEscolhidoSet)
{
	this->TimeEscolhido = TimeEscolhidoSet;
}
