//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "GameFramework/Actor.h"
#include "ObjetivoNPC.generated.h"

UCLASS()
class DEVLOPWAR_API AObjetivoNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjetivoNPC();

	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;

	UPROPERTY(Replicated,BlueprintReadWrite)
	float Vida = 500;

	UPROPERTY(Replicated)
	ETime TimeTerritorio = ETime::Nenhum;

	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	int IndexTerritorio = 1;

	UPROPERTY(Replicated,BlueprintReadWrite)
	bool EstaBloqueado = false;

	UFUNCTION(Reliable,Server)
	void ContadorTempo();

	FTimerHandle Contador;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
