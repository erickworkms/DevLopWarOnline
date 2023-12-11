//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWar/Controles/GamePlayController.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/Personagens/NPC/NPC_Base.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::DanoAtaqueProjetil_Implementation(AActor* DonoProjetil, AActor* InimigoDetectado,
                                                           AActor* Projetil)
{
	AJogador_Base* Jogador_Detectado = Cast<AJogador_Base>(InimigoDetectado);
	AJogador_Base* Inimigo = Cast<AJogador_Base>(DonoProjetil);
	AObjetivoNPC* Territorio = Cast<AObjetivoNPC>(InimigoDetectado);
	ANPC_Base* NPC_Detectado = Cast<ANPC_Base>(InimigoDetectado);

	int DonoIndex = 0;
	int AlvoIndex = 0;

	if (IsValid(Jogador_Detectado))
	{
		if (Jogador_Detectado->Vida > 0)
		{
			for (int i = 0; i < JogadoresSala.Num(); i++)
			{
				if (IsValid(JogadoresSala[i]))
				{
					if (JogadoresSala[i] == Jogador_Detectado->GetController())
					{
						AlvoIndex = i;
					}
					else if (JogadoresSala[i] == Inimigo->GetController())
					{
						DonoIndex = i;
					}
				}
			}
			Jogador_Detectado->Vida -= Inimigo->QuantidadeDano;

			if (Jogador_Detectado->Vida <= 0)
			{
				AGamePlayController* JogadorControle = Cast<AGamePlayController>(JogadoresSala[AlvoIndex]);
				AlterarNumJogadoresMortos(DonoIndex);
				AlterarNumMortes(AlvoIndex);
				GetWorldTimerManager().SetTimer(ReviverContador, JogadorControle, &AGamePlayController::ReviveJogador, 5, false);
			}
		}
		Projetil->Destroy();
	}


	if (IsValid(NPC_Detectado))
	{
		if (NPC_Detectado->Vida > 0)
		{
			for (int i = 0; i < JogadoresSala.Num(); i++)
			{
				if (IsValid(JogadoresSala[i]))
				{
					if (JogadoresSala[i] == Inimigo->GetController())
					{
						DonoIndex = i;
					}
				}
			}
			NPC_Detectado->Vida -= Inimigo->QuantidadeDano;
			if (NPC_Detectado->Vida <= 0)
			{
				AlterarNumZumbiesMortos(DonoIndex);
			}
		}
		Projetil->Destroy();
	}
	else if (IsValid(Territorio))
	{
		for (int i = 0; i < JogadoresSala.Num(); i++)
		{
			if (IsValid(JogadoresSala[i]))
			{
				if (JogadoresSala[i] == Inimigo->GetController())
				{
					DonoIndex = i;
				}
			}
		}
		if (Territorio->Vida > 0 && Territorio->EstaBloqueado == false && !GameStateServer->GetVerificaTerritorioConquistado(Territorio->IndexTerritorio,InformacaoGameplay[DonoIndex].TimeEscolhido))
		{
			Territorio->Vida -= Inimigo->QuantidadeDano;
			
			switch (Territorio->IndexTerritorio)
			{
			case 1:
				GameStateServer->SetVidaTerritorio1(Territorio->Vida);
				break;
			case 2:
				GameStateServer->SetVidaTerritorio2(Territorio->Vida);
				break;
			case 3:
				GameStateServer->SetVidaTerritorio3(Territorio->Vida);
				break;
			case 4:
				GameStateServer->SetVidaTerritorio4(Territorio->Vida);
				break;
			default:
				break;
			}
			
			
			if (Territorio->Vida <= 0)
			{
				Territorio->Vida = 100;
				switch (Territorio->IndexTerritorio)
				{
				case 1:
					GameStateServer->SetDonoTerritorio1(InformacaoGameplay[DonoIndex].TimeEscolhido);
					GameStateServer->SetVidaTerritorio1(Territorio->Vida);
					break;
				case 2:
					GameStateServer->SetDonoTerritorio2(InformacaoGameplay[DonoIndex].TimeEscolhido);
					GameStateServer->SetVidaTerritorio2(Territorio->Vida);
					break;
				case 3:
					GameStateServer->SetDonoTerritorio3(InformacaoGameplay[DonoIndex].TimeEscolhido);
					GameStateServer->SetVidaTerritorio3(Territorio->Vida);
					break;
				case 4:
					GameStateServer->SetDonoTerritorio4(InformacaoGameplay[DonoIndex].TimeEscolhido);
					GameStateServer->SetVidaTerritorio4(Territorio->Vida);
					break;
				default:
					break;
				}
				Territorio->EstaBloqueado = true;
				ReativaPontosObjetivo(Territorio->IndexTerritorio,Territorio->EstaBloqueado);
				GetWorldTimerManager().SetTimer(Territorio->Contador, Territorio, &AObjetivoNPC::ContadorTempo, 5, false);
			}
		}
		Projetil->Destroy();
	}
	else if (InimigoDetectado != DonoProjetil)
	{
		Projetil->Destroy();
	}
}
