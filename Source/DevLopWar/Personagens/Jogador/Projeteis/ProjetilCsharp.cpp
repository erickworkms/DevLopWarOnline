// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetilCsharp.h"

AProjetilCsharp::AProjetilCsharp()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ProjetilContainer(
			TEXT("StaticMesh'/Game/Personagens/Arma/csharp.csharp'"));
	if (ProjetilContainer.Succeeded())
	{
		ProjetilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProjetil"));
		ProjetilMesh->SetStaticMesh(ProjetilContainer.Object);
		ProjetilMesh->SetSimulatePhysics(true);
		ProjetilMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
		SetRootComponent(ProjetilMesh);

		Projetil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projetil"));
		Projetil->SetUpdatedComponent(ProjetilMesh);
		Projetil->InitialSpeed = 3000.f;
		Projetil->MaxSpeed = 3000.f;
		Projetil->bRotationFollowsVelocity = true;
		Projetil->bShouldBounce = false;
		Projetil->bSimulationEnabled = true;
		ProjetilMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjetil::InicioDanoColisao);
		SetReplicates(true);
	}
}
