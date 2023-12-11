//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/Controles/GamePlayController.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::AcessaInformacoesTime(TArray<APlayerController*> ListaJogadores)
{
	for (int i=0;i < ListaJogadores.Num();i++)
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(ListaJogadores[i]);
		FInformacaoJogadorGameplay InfAux;
		InfAux.NumZumbiesMortos = PlayerState->GetNumZumbiesMortos();
		InfAux.NumJogadoresMortos = PlayerState->GetNumJogadoresMortos();
		InfAux.NumMortes = PlayerState->GetNumMortes();
		InfAux.TimeEscolhido = PlayerState->GetTimeEscolhido();
		InformacaoGameplay.Add(InfAux);
	}
}


void ADevLopWarGameMode::CriaInformacoesJogadorServer_Implementation(AGamePlayController* Controle,FInformacaoJogadorGameplay InformacaoGameplayLocal,int IndexJogador)
{
	JogadoresSala[IndexJogador] = Controle;
	InformacaoGameplay[IndexJogador] = InformacaoGameplayLocal;
}
