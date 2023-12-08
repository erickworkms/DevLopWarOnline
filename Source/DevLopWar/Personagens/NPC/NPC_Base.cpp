//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "NPC_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "IAControle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "Net/UnrealNetwork.h"


ANPC_Base::ANPC_Base()
{
	VerificaPadroes();
}


void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	VariaveisIA_BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(GetController());
	ControleNPC = Cast<AIAControle>(GetController());
	VerificaLocalPatrulha();
}


void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetController())
	{
		DefineEstadoAtual();
		DefinePadroesVel(DeltaTime);
		VerificaVida();
		GerenciaVisaoPersonagemIA();
		if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
		{
			VerificaMetodoComportamento();
		}
	}
	else
	{
		if (Acao == Morto)
		{
			GetCharacterMovement()->SetCanEverAffectNavigation(false);
			GetCharacterMovement()->SetAvoidanceEnabled(false);
			if (IsValid(InimigoEncontrado))
			{
				InimigoEncontrado = NULL;
			}
			SetActorTickEnabled(false);
		}
	}
}

void ANPC_Base::VerificaVida_Implementation()
{
	if (Vida <= 0)
	{
		IA_Comportamento = Morto_NPC;
	}
}

void ANPC_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPC_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANPC_Base, Vida);
	DOREPLIFETIME(ANPC_Base, Velocidade);
	DOREPLIFETIME(ANPC_Base, VelocidadeMax);
	DOREPLIFETIME(ANPC_Base, DistanciaCombate);
	
	DOREPLIFETIME(ANPC_Base, PodeMovimentar);
	
	DOREPLIFETIME(ANPC_Base, Estado);
	DOREPLIFETIME(ANPC_Base, Acao);
	DOREPLIFETIME(ANPC_Base, IA_Comportamento);
	
	DOREPLIFETIME(ANPC_Base, DanoAtaque);
	DOREPLIFETIME(ANPC_Base, LocalObjetivoPatrulha);
}

void ANPC_Base::DefinePadroesVel_Implementation(float valor)
{
	if (IA_Comportamento == Perseguir_NPC && Acao != Atacar && PodeMovimentar == true)
	{
		VelocidadeMax = 400;
	}
	else if (PodeMovimentar == false)
	{
		VelocidadeMax = 0;
	}
	else
	{
		VelocidadeMax = 100;
	}
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
								  Velocidade, valor, 10.f);
	
	if (Vida <= 0.0f)
	{
		Acao = Morto;
		VelocidadeMax = 0;
		ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void ANPC_Base::VerificaPadroes()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);

	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Clientes/Mremireh_O_Desbiens.Mremireh_O_Desbiens'"));
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
			TEXT("AnimBlueprint'/Game/Personagens/Clientes/Clientes_AnimBlueprint.Clientes_AnimBlueprint'"));
	GetMesh()->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);

	//floats
	Vida = 100;
	DistanciaCombate = 100;

	//Structs
	Acao = Nada;
	Estado = NoChaoAndando;
	IA_Comportamento = Patrulha_NPC;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AIAControle::StaticClass();
	
	GetCharacterMovement()->SetAvoidanceEnabled(true);
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 500;

	DanoAtaque = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisaoAtaque"));
	DanoAtaque->bFillCollisionUnderneathForNavmesh = false;
	DanoAtaque->bHiddenInGame = false;
	DanoAtaque->SetVisibility(true);
	DanoAtaque->SetCanEverAffectNavigation(false);
	DanoAtaque->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	DanoAtaque->SetRelativeRotation(FRotator(0, 0, 0));
	DanoAtaque->SetWorldScale3D(FVector(1, 0.5, 2));
	DanoAtaque->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DanoAtaque->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	DanoAtaque->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	DanoAtaque->OnComponentBeginOverlap.AddDynamic(this, &ANPC_Base::InicioDanoColisao);
	DanoAtaque->OnComponentEndOverlap.AddDynamic(this, &ANPC_Base::FimDanoColisao);
	DanoAtaque->AttachToComponent(GetMesh(),
							FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoEsqSoquete");
}

void ANPC_Base::DefineEstadoAtual_Implementation()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		Estado = Caindo;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		Estado = Voando;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		Estado = NoChaoAndando;
	}
	else
	{
		Estado = NoChaoAndando;
	}
}

void ANPC_Base::VerificaLocalPatrulha_Implementation()
{
	VariaveisIA_BlackBoard->SetValueAsVector("LocalObjetivo", LocalObjetivoPatrulha->GetActorLocation());
}

void ANPC_Base::MoverPersonagemPatrulha_Implementation(FVector LocalPatrulha)
{
	if (IA_Comportamento == Patrulha_NPC)
	{
		VerificaLocalPatrulha();
		ControleNPC->MoveToLocation(LocalPatrulha, 25, true, true,
											true, false, 0, false);
	}
	else if (IA_Comportamento == Perseguir_NPC)
	{
		if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) >= DistanciaCombate)
		{
			Acao = Nada;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->MoveToLocation(InimigoEncontrado->GetActorLocation(), 25, true, true,
											true, false, 0, false);
			ControleNPC->ClearFocus(EAIFocusPriority::Default);
		}
		else if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) <= DistanciaCombate && Acao != Atacar && PodeMovimentar == true)
		{
			PodeMovimentar = false;
			Acao = Atacar;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->SetFocus(InimigoEncontrado);
		}
	}
}

void ANPC_Base::VerificaMetodoComportamento_Implementation()
{
	if (Estado == NoChaoAndando)
	{
		if (IA_Comportamento == Patrulha_NPC)
		{
			MoverPersonagemPatrulha(VariaveisIA_BlackBoard->GetValueAsVector("LocalObjetivo"));
		}
		if (IA_Comportamento == Perseguir_NPC)
		{
			if (IsValid(InimigoEncontrado))
			{
				MoverPersonagemPatrulha(InimigoEncontrado->GetActorLocation());
			}
		}
	}
	else{
		ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
		GetCharacterMovement()->StopActiveMovement();
		ControleNPC->StopMovement();
		Acao = Nada;
	}
}

void ANPC_Base::GerenciaEscolhaInimigoIA()
{
	AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);

	if (IsValid(JogadorPadrao))
	{
		VariaveisIA_BlackBoard->SetValueAsObject("Inimigo", JogadorPadrao);
	}
}

void ANPC_Base::GerenciaVisaoPersonagemIA_Implementation()
{
	if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
	{
		if (InimigoEncontrado)
		{
			float AuxDistancia = GetDistanceTo(InimigoEncontrado);
			if (AuxDistancia < 3000)
			{
				VariaveisIA_BlackBoard->SetValueAsFloat("DistanciaObjetivo", AuxDistancia);
				IA_Comportamento = Perseguir_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
			else
			{
				InimigoEncontrado = NULL;
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
	if (IsValid(InimigoEncontrado))
	{
		AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);
		if (IsValid(JogadorPadrao))
		{
			if (JogadorPadrao->Vida <= 0)
			{
				InimigoEncontrado = NULL;
				ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				Acao = Nada;
				VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
}
