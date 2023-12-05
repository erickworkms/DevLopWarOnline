//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "GamePlayController.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Net/UnrealNetwork.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"


void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	SetReplicates(true);
}

void AGamePlayController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePlayController, Personagem);
}


void AGamePlayController::CriaPersonagem_Implementation()
{
	UWorld* World = GetWorld();
	check(World);
	TArray<AActor*> PlayerStartEncontrados;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		PlayerStartEncontrados.Add(*It);
	}
	APlayerStart* PontoEscolhido = nullptr;
	if (PlayerStartEncontrados.Num() > 0)
	{
		PontoEscolhido = Cast<APlayerStart>(
			PlayerStartEncontrados[FMath::RandRange(0, PlayerStartEncontrados.Num() - 1)]);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, PontoEscolhido->GetActorLocation().ToString());
	}
	if (PontoEscolhido)
	{
		Personagem = GetWorld()->SpawnActorDeferred<AJogador_Base>(
			AJogador_Base::StaticClass(),
			FTransform(PontoEscolhido->GetActorRotation(),
			           PontoEscolhido->GetActorLocation()));
		if (Personagem)
		{
			Personagem->FinishSpawning(FTransform(PontoEscolhido->GetActorRotation(),
			                                      PontoEscolhido->GetActorLocation()));
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Personagem->GetName());
		bShowMouseCursor = false;
		SetPawn(Personagem);
		Possess(Personagem);
	}
}

void AGamePlayController::EscolhePersonagem_Implementation(TipoPersonagem PersonagemNPC)
{
	if (IsValid(GetPawn()) && HasAuthority())
	{
		Personagem = Cast<AJogador_Base>(GetPawn());
		if (IsValid(Personagem))
		{
			bShowMouseCursor = false;
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->VerificaEscolhaPersonagem();
			EscolhePersonagemCliente(PersonagemNPC);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "falhou no personagem");
	}
}

void AGamePlayController::EscolhePersonagemCliente_Implementation(TipoPersonagem PersonagemNPC)
{
	if (IsValid(GetPawn()))
	{
		Personagem = Cast<AJogador_Base>(GetPawn());
		if (IsValid(Personagem))
		{
			bShowMouseCursor = false;
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->VerificaEscolhaPersonagem();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "falhou no personagem");
	}
}
