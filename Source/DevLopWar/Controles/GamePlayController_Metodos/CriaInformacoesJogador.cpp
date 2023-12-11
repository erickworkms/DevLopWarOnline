//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"

void AGamePlayController::AdicionaDadosInstanceServer_Implementation()
{
	AdicionaPlayerListaServidor(this,CriaInformacoesJogador(),RetornaIndexJogador());
}

FInformacaoJogadorGameplay AGamePlayController::CriaInformacoesJogador()
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	FInformacaoJogadorGameplay InformacaoGameplay;
	InformacaoGameplay.NumZumbiesMortos = 0;
	InformacaoGameplay.NumJogadoresMortos = 0;
	InformacaoGameplay.NumMortes = 0;
	InformacaoGameplay.TimeEscolhido = PlayerInstance->Time;
	return InformacaoGameplay;
}
int AGamePlayController::RetornaIndexJogador()
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	return PlayerInstance->IndexJogador;
}
void AGamePlayController::AdicionaPlayerListaServidor_Implementation(AGamePlayController* Controle,FInformacaoJogadorGameplay InformacaoGameplay,int IndexJogador)
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	if (IsValid(GameMode))
	{
		ADevLopWarGameMode* DevGameMode = Cast<ADevLopWarGameMode>(GameMode);
		if (IsValid(DevGameMode))
		{
			//UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
			DevGameMode->CriaInformacoesJogadorServer(Controle,InformacaoGameplay,IndexJogador);
			VerificaDadosInstance(InformacaoGameplay);
		}
	}
}