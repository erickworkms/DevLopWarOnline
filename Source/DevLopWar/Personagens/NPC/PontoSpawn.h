// Fill out your copyright notice in the Description page of Project Settings.

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
