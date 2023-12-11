// Fill out your copyright notice in the Description page of Project Settings.


#include "PontoSpawn.h"

// Sets default values
APontoSpawn::APontoSpawn()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
			TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
		LocalReferenciaNPC->bFillCollisionUnderneathForNavmesh = false;
		LocalReferenciaNPC->SetCanEverAffectNavigation(false);
	}

	LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LocalReferenciaNPC->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocalReferenciaNPC->bHiddenInGame = true;

	SetReplicates(true);
}
