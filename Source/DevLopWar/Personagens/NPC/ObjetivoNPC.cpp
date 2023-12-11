//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "ObjetivoNPC.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"

AObjetivoNPC::AObjetivoNPC()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
	}

	LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SetReplicates(true);
}

void AObjetivoNPC::ContadorTempo_Implementation()
{
	AGameModeBase* GameModeEncontrado = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeEncontrado);
	EstaBloqueado = false;
	GameMode->ReativaPontosObjetivo(IndexTerritorio,EstaBloqueado);
}

void AObjetivoNPC::BeginPlay()
{
	Super::BeginPlay();
}

void AObjetivoNPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


