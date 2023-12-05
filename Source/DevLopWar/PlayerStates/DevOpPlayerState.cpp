// Fill out your copyright notice in the Description page of Project Settings.


#include "DevOpPlayerState.h"

#include "Net/UnrealNetwork.h"

void ADevOpPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevOpPlayerState,hudDetectada);
}
