// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyController.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "DevLopWarGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UDevLopWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString token;
	UPROPERTY(BlueprintReadWrite)
	FString NomeJogador;
	UPROPERTY(BlueprintReadWrite)
	ALobbyController* ControleLobby;
	
	FOnlineSessionSettings SessionSettings;
	IOnlineSessionPtr SessionInt;
};
