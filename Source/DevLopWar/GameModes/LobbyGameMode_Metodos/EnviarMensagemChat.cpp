//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controles/LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"

void ALobbyGameMode::EnviarMensagemChat_Implementation(const FString& mensagem)
{
	UWorld* World = GetWorld();
	check(World);
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < JogadoresSala.Num();i++)
		{
			if (IsValid(JogadoresSala[i]))
			{
				ALobbyController* PlayerState = Cast<ALobbyController>(JogadoresSala[i]);
				if (IsValid(PlayerState))
				{
					PlayerState->EnviarMensagemCliente(JogadoresSala[i]->GetName(),mensagem);
				}
			}
		}
	}
}
