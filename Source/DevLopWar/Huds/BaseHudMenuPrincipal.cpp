// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHudMenuPrincipal.h"

#include "Kismet/GameplayStatics.h"

ABaseHudMenuPrincipal::ABaseHudMenuPrincipal()
{

}

void ABaseHudMenuPrincipal::CriaSalaHost()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MapaJogavel"));
}

void ABaseHudMenuPrincipal::ProcuraSalaHost()
{
}

void ABaseHudMenuPrincipal::ConectaSalaHost()
{
}
