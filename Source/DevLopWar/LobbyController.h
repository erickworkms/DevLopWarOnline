// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Huds/BaseHudMenuPrincipal.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyController();
	UFUNCTION()
	void EnviarMensagem();

	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* HudChat;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
};
