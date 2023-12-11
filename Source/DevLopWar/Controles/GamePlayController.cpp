//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "GamePlayController.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Personagens/NPC/PontoSpawn.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"


void AGamePlayController::ReviveJogador_Implementation()
{
	UWorld* World = GetWorld();
	check(World);
	
	AJogador_Base* Jogador = Cast<AJogador_Base>(GetPawn());
	Jogador->Vida = 100;
	Jogador->Acao = Nada;
	
	if (GetLocalRole() == ROLE_Authority)
	{
		TArray<APontoSpawn*> Objetivo;
		for (TActorIterator<APontoSpawn> It(World); It; ++It)
		{
			Objetivo.Add(*It);
		}
		if (Objetivo.Num() > 0)
		{
			APontoSpawn* ObjetoEscolhido = Objetivo[FMath::RandRange(0, Objetivo.Num() - 1)];
			FVector Local = ObjetoEscolhido->GetActorLocation();
			// Jogador->TeleportTo(FVector(Local.X,Local.Y,Local.Z + 50),ObjetoEscolhido->GetActorRotation(),false,true);
			Jogador->SetActorLocationAndRotation(FVector(Local.X,Local.Y,Local.Z + 50),ObjetoEscolhido->GetActorRotation(), false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}

void AGamePlayController::AtivaHudFimPartida_Implementation()
{
	if (IsValid(Hud))
	{
		Hud->AtivarTelaVencedor();
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,"falhou");
	}
}

void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
}

void AGamePlayController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePlayController, Personagem);
	DOREPLIFETIME(AGamePlayController, Hud);
}

void AGamePlayController::VerificaDadosInstance_Implementation(FInformacaoJogadorGameplay InformacaoGameplay)
{
	ADevOpPlayerState* PlayerStateDados = Cast<ADevOpPlayerState>(PlayerState);
	if (IsValid(PlayerState))
	{
		PlayerStateDados->SetTimeEscolhido(InformacaoGameplay.TimeEscolhido);
	}
}
