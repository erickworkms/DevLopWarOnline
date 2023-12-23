//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PontoSpawn.generated.h"

UCLASS()
class DEVLOPWAR_API APontoSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APontoSpawn();

	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;

};
