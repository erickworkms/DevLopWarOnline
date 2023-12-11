//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controles/LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::DesconectaCliente_Implementation(APlayerController* PlayerController, int32 Id)
{
	if (IsValid(JogadoresSala[Id]) && GetLocalRole() == ROLE_Authority)
	{
		JogadoresSala[Id]->ClientTravel("/Game/Mapas/TelaInicial", ETravelType::TRAVEL_Absolute);
		JogadoresSala.RemoveAt(Id);
		JogadoresSalaNome.RemoveAt(Id);
	}
	for (int i=0;i < JogadoresSala.Num();i++)
	{
		if (IsValid(JogadoresSala[i]))
		{
			ALobbyController* Controle = Cast<ALobbyController>(JogadoresSala[i]);
			Controle->VerEntradaLogin(JogadoresSalaNome);
		}
	}
}

bool ALobbyGameMode::DesconectaCliente_Validate(APlayerController* PlayerController, int32 Id)
{
	if (Id == 0 && GetLocalRole() == ROLE_Authority)
	{
		APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		DefaultPlayerController->ClientTravel("/Game/Mapas/TelaInicial", ETravelType::TRAVEL_Absolute);
	}
	else if (IsValid(JogadoresSala[Id]) && GetLocalRole() == ROLE_Authority)
	{
		return true;
	}
	return false;
}

void ALobbyGameMode::ExcluirSala()
{
	if (GameInstance->SessionInt.IsValid())
	{
		FString NomeDaSala;
		GameInstance->SessionSettings.Get(NAME_GameSession, NomeDaSala);
		GameInstance->SessionInt->DestroySession(*NomeDaSala);
	}
}