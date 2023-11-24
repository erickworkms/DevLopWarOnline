// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Base.h"
#include "Navigation/PathFollowingComponent.h"
#include "AI/Navigation/NavigationAvoidanceTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "IAControle.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API AIAControle : public AAIController
{
	GENERATED_BODY()

public:
	AIAControle();
	
	FString CaminhoArvoreEstados;
	UPROPERTY()
	UBehaviorTree* ArvoreEstados;
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* Detector;
	UPROPERTY()
	UAISenseConfig_Sight* ConfigDetector;
	UPROPERTY()
	UBlackboardComponent* Variaveis_IA_Comp;
	UPROPERTY()
	UBlackboardData* Variaveis_AI_Data;
	UPROPERTY()
	ANPC_Base* NPC_Ref;


	virtual UAIPerceptionComponent* GetPerceptionComponent() override;

	void PadroesSensor();
	void IniciaSensor();
	void AdicionaVariaveisIA();
	UFUNCTION()
	void DetectaPresenca(AActor* Per,FAIStimulus estimulo);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
