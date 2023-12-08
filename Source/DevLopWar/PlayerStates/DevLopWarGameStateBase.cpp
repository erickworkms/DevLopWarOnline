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
	VidaTerritorio1 -= VidaTerritorio1Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio2()
{
	return VidaTerritorio2;
}

void ADevLopWarGameStateBase::SetVidaTerritorio2_Implementation(float VidaTerritorio2Set)
{
	VidaTerritorio2 -= VidaTerritorio2Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio3()
{
	return VidaTerritorio3;
}

void ADevLopWarGameStateBase::SetVidaTerritorio3_Implementation(float VidaTerritorio3Set)
{
	VidaTerritorio3 -= VidaTerritorio3Set;
}

float ADevLopWarGameStateBase::GetVidaTerritorio4()
{
	return VidaTerritorio4;
}

void ADevLopWarGameStateBase::SetVidaTerritorio4_Implementation(float VidaTerritorio4Set)
{
	VidaTerritorio4 -= VidaTerritorio4Set;
}

ETime ADevLopWarGameStateBase::GetTimeVencedor()
{
	return TimeVencedor;
}

void ADevLopWarGameStateBase::SetTimeVencedor_Implementation(ETime TimeVencedorSet)
{
	TimeVencedor = TimeVencedorSet;
}

ETime ADevLopWarGameStateBase::GetVidaTerritorio1Dono()
{
	return VidaTerritorio1Dono;
}

void ADevLopWarGameStateBase::SetVidaTerritorio1Dono_Implementation(ETime VidaTerritorio1DonoSet)
{
	VidaTerritorio1Dono = VidaTerritorio1DonoSet;
}

ETime ADevLopWarGameStateBase::GetVidaTerritorio2Dono()
{
	return VidaTerritorio2Dono;
}

void ADevLopWarGameStateBase::SetVidaTerritorio2Dono_Implementation(ETime VidaTerritorio2DonoSet)
{
	VidaTerritorio2Dono = VidaTerritorio2DonoSet;
}
ETime ADevLopWarGameStateBase::GetVidaTerritorio3Dono()
{
	return VidaTerritorio3Dono;
}

void ADevLopWarGameStateBase::SetVidaTerritorio3Dono_Implementation(ETime VidaTerritorio3DonoSet)
{
	VidaTerritorio3Dono = VidaTerritorio3DonoSet;
}
ETime ADevLopWarGameStateBase::GetVidaTerritorio4Dono()
{
	return VidaTerritorio4Dono;
}

void ADevLopWarGameStateBase::SetVidaTerritorio4Dono_Implementation(ETime VidaTerritorio4DonoSet)
{
	VidaTerritorio4Dono = VidaTerritorio4DonoSet;
}
