// Fill out your copyright notice in the Description page of Project Settings.

#include "DevLopWarGameStateBase.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Net/UnrealNetwork.h"

ADevLopWarGameStateBase::ADevLopWarGameStateBase()
{
}

void ADevLopWarGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevLopWarGameStateBase, TempoJogo);
	DOREPLIFETIME(ADevLopWarGameStateBase, VidaTerritorio1);
	DOREPLIFETIME(ADevLopWarGameStateBase, VidaTerritorio2);
	DOREPLIFETIME(ADevLopWarGameStateBase, VidaTerritorio3);
	DOREPLIFETIME(ADevLopWarGameStateBase, VidaTerritorio4);
	DOREPLIFETIME(ADevLopWarGameStateBase, DonoTerritorio1);
	DOREPLIFETIME(ADevLopWarGameStateBase, DonoTerritorio2);
	DOREPLIFETIME(ADevLopWarGameStateBase, DonoTerritorio3);
	DOREPLIFETIME(ADevLopWarGameStateBase, DonoTerritorio4);
	DOREPLIFETIME(ADevLopWarGameStateBase, TimeVencedor);
}

float ADevLopWarGameStateBase::GetTempoJogo()
{
	return TempoJogo;
}

void ADevLopWarGameStateBase::SetTempoJogo_Implementation(float TempoJogoSet)
{
	TempoJogo = TempoJogoSet;
}

float ADevLopWarGameStateBase::GetVidaTerritorio1()
{
	return VidaTerritorio1;
}

void ADevLopWarGameStateBase::SetVidaTerritorio1_Implementation(float VidaTerritorio1Set)
{
	VidaTerritorio1 = VidaTerritorio1Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio2()
{
	return VidaTerritorio2;
}

void ADevLopWarGameStateBase::SetVidaTerritorio2_Implementation(float VidaTerritorio2Set)
{
	VidaTerritorio2 = VidaTerritorio2Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio3()
{
	return VidaTerritorio3;
}

void ADevLopWarGameStateBase::SetVidaTerritorio3_Implementation(float VidaTerritorio3Set)
{
	VidaTerritorio3 = VidaTerritorio3Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio4()
{
	return VidaTerritorio4;
}

void ADevLopWarGameStateBase::SetVidaTerritorio4_Implementation(float VidaTerritorio4Set)
{
	VidaTerritorio4 = VidaTerritorio4Set;
}


ETime ADevLopWarGameStateBase::GetTimeVencedor()
{
	return TimeVencedor;
}

void ADevLopWarGameStateBase::SetTimeVencedor_Implementation()
{
	int ContadorClientes = 0;
	int ContadorAgil = 0;
	int ContadorCascade = 0;
	if (DonoTerritorio1 == ETime::Clientes)
	{
		ContadorClientes++;
	}
	else if (DonoTerritorio1 == ETime::Agil)
	{
		ContadorAgil++;
	}
	else if (DonoTerritorio1 == ETime::Cascade)
	{
		ContadorCascade++;
	}
	//
	if (DonoTerritorio2 == ETime::Clientes)
	{
		ContadorClientes++;
	}
	else if (DonoTerritorio2 == ETime::Agil)
	{
		ContadorAgil++;
	}
	else if (DonoTerritorio2 == ETime::Cascade)
	{
		ContadorCascade++;
	}

	if (DonoTerritorio3 == ETime::Clientes)
	{
		ContadorClientes++;
	}
	else if (DonoTerritorio3 == ETime::Agil)
	{
		ContadorAgil++;
	}
	else if (DonoTerritorio3 == ETime::Cascade)
	{
		ContadorCascade++;
	}

	if (DonoTerritorio4 == ETime::Clientes)
	{
		ContadorClientes++;
	}
	else if (DonoTerritorio4 == ETime::Agil)
	{
		ContadorAgil++;
	}
	else if (DonoTerritorio4 == ETime::Cascade)
	{
		ContadorCascade++;
	}

	if (ContadorClientes > ContadorAgil && ContadorClientes > ContadorCascade)
	{
		TimeVencedor = ETime::Clientes;
	}
	else if (ContadorAgil > ContadorClientes && ContadorAgil > ContadorCascade)
	{
		TimeVencedor = ETime::Agil;
	}
	else if (ContadorCascade > ContadorAgil && ContadorCascade > ContadorClientes)
	{
		TimeVencedor = ETime::Cascade;
	}
	else
	{
		TimeVencedor = ETime::Nenhum;
	}
}

ETime ADevLopWarGameStateBase::GetDonoTerritorio1()
{
	return DonoTerritorio1;
}

bool ADevLopWarGameStateBase::GetBloqueioTerritorio1()
{
	return BloqueioTerritorio1;
}

void ADevLopWarGameStateBase::SetBloqueioTerritorio1_Implementation(bool BloqueioTerritorio1Set)
{
	BloqueioTerritorio1 = BloqueioTerritorio1Set;
}

bool ADevLopWarGameStateBase::GetBloqueioTerritorio2()
{
	return BloqueioTerritorio2;
}

void ADevLopWarGameStateBase::SetBloqueioTerritorio2_Implementation(bool BloqueioTerritorio2Set)
{
	BloqueioTerritorio2 = BloqueioTerritorio2Set;
}

bool ADevLopWarGameStateBase::GetBloqueioTerritorio3()
{
	return BloqueioTerritorio3;
}

void ADevLopWarGameStateBase::SetBloqueioTerritorio3_Implementation(bool BloqueioTerritorio3Set)
{
	BloqueioTerritorio3 = BloqueioTerritorio3Set;
}

bool ADevLopWarGameStateBase::GetBloqueioTerritorio4()
{
	return BloqueioTerritorio4;
}

void ADevLopWarGameStateBase::SetBloqueioTerritorio4_Implementation(bool BloqueioTerritorio4Set)
{
	BloqueioTerritorio4 = BloqueioTerritorio4Set;
}

void ADevLopWarGameStateBase::SetDonoTerritorio1_Implementation(ETime DonoTerritorio1Set)
{
	DonoTerritorio1 = DonoTerritorio1Set;
}

ETime ADevLopWarGameStateBase::GetDonoTerritorio2()
{
	return DonoTerritorio2;
}

void ADevLopWarGameStateBase::SetDonoTerritorio2_Implementation(ETime DonoTerritorio2Set)
{
	DonoTerritorio2 = DonoTerritorio2Set;
}

ETime ADevLopWarGameStateBase::GetDonoTerritorio3()
{
	return DonoTerritorio3;
}

void ADevLopWarGameStateBase::SetDonoTerritorio3_Implementation(ETime DonoTerritorio3Set)
{
	DonoTerritorio3 = DonoTerritorio3Set;
}

ETime ADevLopWarGameStateBase::GetDonoTerritorio4()
{
	return DonoTerritorio4;
}

void ADevLopWarGameStateBase::SetDonoTerritorio4_Implementation(ETime DonoTerritorio4Set)
{
	this->DonoTerritorio4 = DonoTerritorio4Set;
}

bool ADevLopWarGameStateBase::GetVerificaTerritorioConquistado(int IndexTerritorio, ETime TimeAtualSet)
{
	switch (IndexTerritorio)
	{
	case 1:
		if (TimeAtualSet == GetDonoTerritorio1())
		{
			return true;
		}
		return false;
	case 2:
		if (TimeAtualSet == GetDonoTerritorio2())
		{
			return true;
		}
		return false;
	case 3:
		if (TimeAtualSet == GetDonoTerritorio3())
		{
			return true;
		}
		return false;
	case 4:
		if (TimeAtualSet == GetDonoTerritorio4())
		{
			return true;
		}
		return false;
	default:
		return false;
	}
}
