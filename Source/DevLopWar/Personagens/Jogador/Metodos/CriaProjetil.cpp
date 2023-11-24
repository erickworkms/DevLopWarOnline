#include "Components/SkeletalMeshComponent.h"
#include "DevLopWar/Personagens/Jogador/Jogador_Base.h"
#include "DevLopWar/Personagens/Jogador/Projeteis/ProjetilCMais.h"
#include "DevLopWar/Personagens/Jogador/Projeteis/ProjetilCsharp.h"
#include "DevLopWar/Personagens/Jogador/Projeteis/ProjetilJava.h"
#include "DevLopWar/Personagens/Jogador/Projeteis/ProjetilNoCode.h"

void AJogador_Base::CriaProjetil()
{
	LocalSocketArma = Arma->GetSocketLocation("TiroSocket");
	RotacaoSocketArma = Arma->GetSocketRotation("TiroSocket");
	
	CriaProjetilServidor(LocalSocketArma,RotacaoSocketArma);
}


void AJogador_Base::CriaProjetilServidor_Implementation(FVector Local,FRotator Rotacao)
{
	AProjetilNoCode* ProjetilEstagiario;
	AProjetilCsharp* ProjetilPleno;
	AProjetilJava* ProjetilSenior;
	AProjetilCMais* ProjetilChefe;

	
	switch (PersonagemNPC)
	{
	case Estagiario:
		QuantidadeDano = 10;
		VelocidadeTiro = 0.5;
		ProjetilEstagiario = GetWorld()->SpawnActor<AProjetilNoCode>(
			Local, Rotacao);
		ProjetilEstagiario->DonoProjetil = this;
		break;
	case Pleno:
		QuantidadeDano = 10;
		VelocidadeTiro = 0.2;
		ProjetilPleno = GetWorld()->SpawnActor<AProjetilCsharp>(Local, Rotacao);
		ProjetilPleno->DonoProjetil = this;
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
									  + "personagem" + GetName() +"  "+ "Atirou");
		break;
	case Senior:
		QuantidadeDano = 5;
		VelocidadeTiro = 0.1;
		ProjetilSenior = GetWorld()->SpawnActor<AProjetilJava>(Local, Rotacao);
		ProjetilSenior->DonoProjetil = this;
		break;
	case Chefe:
		QuantidadeDano = 50;
		VelocidadeTiro = 1;
		ProjetilChefe = GetWorld()->SpawnActor<AProjetilCMais>(Local, Rotacao);
		ProjetilChefe->DonoProjetil = this;
		break;
	default:
		VelocidadeTiro = 0.1;
		ProjetilSenior = GetWorld()->SpawnActor<AProjetilJava>(Local, Rotacao);
		ProjetilSenior->DonoProjetil = this;
		break;
	}
}
