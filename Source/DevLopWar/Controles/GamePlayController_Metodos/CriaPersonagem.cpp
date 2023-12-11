//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "EngineUtils.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"


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
		bShowMouseCursor = false;
		SetPawn(Personagem);
		Possess(Personagem);
		AdicionaDadosInstanceServer();
	}
}