// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"
#include "DevOpPlayerState.h"
#include "Net/UnrealNetwork.h"

void ALobbyController::EnviarMensagem_Implementation(const FString& nome,const FString& mensagem)
{
	HudChat->EnviaMensagemChat(mensagem);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,"funcionou no cliente");
}

void ALobbyController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

ALobbyController::ALobbyController()
{
	PlayerState = GetPlayerState<ADevOpPlayerState>();
	bReplicates = true;
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyController,HudChat);
}

void ALobbyController::VerEntradaLogin_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,"detectou o player controller"+GetName());
	if (IsValid(HudChat))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,"detectou o player controller"+HudChat->GetName());
		HudChat->AdicionaHudSalas();
	}
}
