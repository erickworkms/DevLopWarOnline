//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "DevLopWar/Controles/LobbyController.h"
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
