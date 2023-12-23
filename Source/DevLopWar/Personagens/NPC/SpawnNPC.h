//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnNPC.generated.h"

UCLASS()
class DEVLOPWAR_API ASpawnNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnNPC();
	
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;
protected:
	FTimerHandle Contador;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Reliable,Server)
	void CriaNPC();
};
