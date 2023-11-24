// Fill out your copyright notice in the Description page of Project Settings.


#include "IAControle.h"

#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Perception/AIPerceptionComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"

AIAControle::AIAControle()
{
	PrimaryActorTick.bCanEverTick = true;
	bStartAILogicOnPossess = true;

	AutoReceiveInput = EAutoReceiveInput::Disabled;
	Possess(GetPawn());
	CaminhoArvoreEstados = TEXT(
		"BehaviorTree'/Game/Personagens/Clientes/Clientes_ArvoreEstados.Clientes_ArvoreEstados'");

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		CaminhoArvore(TEXT("BehaviorTree'/Game/Personagens/Clientes/Clientes_ArvoreEstados.Clientes_ArvoreEstados'"));
	ArvoreEstados = CaminhoArvore.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		CaminhoData(TEXT(
			"BlackboardData'/Game/Personagens/Clientes/ClientesIA_ListaVariaveis.ClientesIA_ListaVariaveis'"));
	Variaveis_AI_Data = CaminhoData.Object;

	Variaveis_IA_Comp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Variaveis_AI_Comp"));

	AdicionaVariaveisIA();

	Variaveis_IA_Comp->InitializeBlackboard(*Variaveis_AI_Data);

	UseBlackboard(Variaveis_AI_Data, Variaveis_IA_Comp);

	Variaveis_IA_Comp->SetValueAsObject("SelfActor", GetPawn());
	
	Detector = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sensor"));
	ConfigDetector = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("ConfigSensor"));

	PadroesSensor();
}

UAIPerceptionComponent* AIAControle::GetPerceptionComponent()
{
	return Super::GetPerceptionComponent();
}

void AIAControle::PadroesSensor()
{
	ConfigDetector->SightRadius = 2000.f;
	ConfigDetector->Implementation = UAISense_Sight::StaticClass();
	ConfigDetector->LoseSightRadius = 1100.f;
	ConfigDetector->PeripheralVisionAngleDegrees = 60.f;
	ConfigDetector->SetMaxAge(2.f);
	ConfigDetector->AutoSuccessRangeFromLastSeenLocation = -1.f;
	ConfigDetector->DetectionByAffiliation.DetectAllFlags();
	ConfigDetector->DetectionByAffiliation.bDetectNeutrals = true;
	ConfigDetector->DetectionByAffiliation.bDetectEnemies = true;
	ConfigDetector->DetectionByAffiliation.bDetectFriendlies = true;

	Detector->ConfigureSense(*ConfigDetector);
	Detector->SetDominantSense(ConfigDetector->GetSenseImplementation());
}

void AIAControle::IniciaSensor()
{
	Detector = GetPerceptionComponent();

	Detector->OnTargetPerceptionUpdated.AddDynamic(this, &AIAControle::DetectaPresenca);

	Detector->UpdatePerceptionWhitelist(ConfigDetector->GetSenseID(), true);
}

void AIAControle::AdicionaVariaveisIA()
{
	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("SelfActor"));
	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("Inimigo"));

	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("Acao"));
	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("Estado"));
	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("IA_Comportamento"));

	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Vector>(FName("LocalObjetivo"));

	Variaveis_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Float>(FName("DistanciaObjetivo"));
}

void AIAControle::DetectaPresenca(AActor* Personagem, FAIStimulus estimulo)
{
	if (estimulo.Type == 0 && NPC_Ref->InimigoEncontrado == NULL)
	{
		AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(Personagem);

		if (JogadorPadrao)
		{
			if (!IsValid(NPC_Ref->InimigoEncontrado))
			{
				NPC_Ref->InimigoEncontrado = JogadorPadrao;
				NPC_Ref->GerenciaEscolhaInimigoIA();
			}
		}
	}
}

void AIAControle::BeginPlay()
{
	Super::BeginPlay();
	NPC_Ref = Cast<ANPC_Base>(GetPawn());
	IniciaSensor();
	RunBehaviorTree(ArvoreEstados);
}
