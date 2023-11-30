// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"
#include "DevOpPlayerState.h"

void ALobbyController::EnviarMensagem()
{

}

void ALobbyController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Enter"), IE_Pressed, this, &ALobbyController::EnviarMensagem);
	SetInputMode(FInputModeGameAndUI());
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
