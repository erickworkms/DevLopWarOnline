// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevLopWarGameMode.generated.h"

UCLASS(minimalapi)
class ADevLopWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ADevLopWarGameMode();

	virtual void BeginPlay() override;

private:
	
};



