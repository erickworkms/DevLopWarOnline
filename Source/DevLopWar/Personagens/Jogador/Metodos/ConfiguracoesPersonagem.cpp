
#include "Components/BoxComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"


void AJogador_Base::DefinePadroes()
{
	MeshesPlayer[0] = TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'");
	MeshesPlayer[1] = TEXT("SkeletalMesh'/Game/Personagens/Pleno/Sporty_Granny.Sporty_Granny'");
	MeshesPlayer[2] = TEXT("SkeletalMesh'/Game/Personagens/Senior/Swat.Swat'");
	MeshesPlayer[3] = TEXT("SkeletalMesh'/Game/Personagens/Chefe/The_Boss.The_Boss'");
	CaminhoArma = TEXT("SkeletalMesh'/Game/Personagens/Arma/Arma.Arma'");
}

void AJogador_Base::VerificaMeshPersonagem_Implementation(float Index)
{
	GetMesh()->SetSkeletalMesh(
		Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index])));
	Arma->SetSkeletalMesh(
		Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *CaminhoArma)));
}

void AJogador_Base::CriaPersonagemConfig()
{
	SetReplicates(true);
	SetReplicateMovement(true);
	
	MeshesPlayer.Init("4", 4);
	DefinePadroes();
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);

	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	}

	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		AnimBlueprint(
			TEXT("AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint'"));
	GetMesh()->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);

	//Blueprints de animação
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		EstagiarioContainer(TEXT(
			"AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint'"));
	if (EstagiarioContainer.Succeeded())
	{
		Estagiario_Anim = EstagiarioContainer.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		PlenoContainer(TEXT(
			"AnimBlueprint'/Game/Personagens/Pleno/Pleno_AnimBlueprint.Pleno_AnimBlueprint'"));
	if (PlenoContainer.Succeeded())
	{
		Pleno_Anim = PlenoContainer.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		SeniorContainer(TEXT(
			"AnimBlueprint'/Game/Personagens/Senior/Senior_AnimBlueprint.Senior_AnimBlueprint'"));
	if (SeniorContainer.Succeeded())
	{
		Senior_Anim = SeniorContainer.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		ChefeContainer(TEXT(
			"AnimBlueprint'/Game/Personagens/Chefe/Chefe_AnimBlueprint.Chefe_AnimBlueprint'"));
	if (ChefeContainer.Succeeded())
	{
		Chefe_Anim = ChefeContainer.Object;
	}

	//Arma
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		ArmaContainer(TEXT("SkeletalMesh'/Game/Personagens/Arma/Arma.Arma'"));
	Arma = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arma"));
	Arma->SetSkeletalMesh(ArmaContainer.Object);
	Arma->AttachToComponent(GetMesh(),
	                        FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoDirSoquete");
	Arma->SetRelativeLocationAndRotation(FVector(0, 0, 0),
	                                     FRotator(0, 0, 0), false, false);


}
