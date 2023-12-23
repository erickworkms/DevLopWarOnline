//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "MenuPrincipalGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "OnlineSubsystemClasses.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Kismet/GameplayStatics.h"


AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudMenuPrincipal"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
}

void AMenuPrincipalGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controle = UGameplayStatics::GetPlayerController(this, 0);

	if (Controle)
	{
		Controle->bShowMouseCursor = true;
		Controle->DefaultMouseCursor = EMouseCursor::Crosshairs;
		GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
		DeletaDadosSala(GameInstance->NomeJogador);
		ChamadaHttp = NewObject<URequisicaoHttp>();
	}
}


void AMenuPrincipalGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void AMenuPrincipalGameMode::DeslogarJogador()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TelaLogin"));
}


