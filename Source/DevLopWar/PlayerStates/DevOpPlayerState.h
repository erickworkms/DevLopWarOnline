// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "DevOpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ADevOpPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated,BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
