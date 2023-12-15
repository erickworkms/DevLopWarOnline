// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnNPC.h"
#include "EngineUtils.h"
#include "ObjetivoNPC.h"
#include "NPC_Base.h"

// Sets default values
ASpawnNPC::ASpawnNPC()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
	}

	LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;
}

void ASpawnNPC::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(Contador, this, &ASpawnNPC::CriaNPC, 5, true);
}

void ASpawnNPC::CriaNPC_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"");
	ANPC_Base* NPC = GetWorld()->SpawnActorDeferred<ANPC_Base>(
			ANPC_Base::StaticClass(),FTransform(GetActorRotation(),GetActorLocation()));
	if (NPC)
	{
		TArray<AObjetivoNPC*> ListaNpcs;
		for (TActorIterator<AObjetivoNPC> It(GetWorld()); It; ++It)
		{
			if (It->TimeTerritorio != ETime::Clientes)
			{
				ListaNpcs.Add(*It);
			}
		}
		NPC->LocalObjetivoPatrulha = ListaNpcs[FMath::RandRange(0, ListaNpcs.Num() - 1)];
		NPC->FinishSpawning(FTransform(GetActorRotation(),GetActorLocation()));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,NPC->LocalObjetivoPatrulha->GetName() + "  este é o territorio encontrado!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"  NPCS falhou");
	}
}
