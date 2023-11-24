// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjetivoNPC.h"

// Sets default values
AObjetivoNPC::AObjetivoNPC()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
	}

	LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AObjetivoNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjetivoNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

