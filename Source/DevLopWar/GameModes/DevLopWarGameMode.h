//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

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
	
};



