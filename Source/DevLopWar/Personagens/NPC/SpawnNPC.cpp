//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


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
		NPC->FinishSpawning(FTransform(GetActorRotation(),GetActorLocation()));}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"  NPCS falhou");
	}
}
