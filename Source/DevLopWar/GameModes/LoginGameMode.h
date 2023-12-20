//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Estruturas/Struct.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "DevLopWar/RequisicoesRede/RequisicaoHttp.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALoginGameMode();

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	URequisicaoHttp* ChamadaHttp;
	
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;

	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
private:
	UFUNCTION(BlueprintCallable)
	void CriarUsuario(FDadosUsuario DadosUsuario);
	UFUNCTION(BlueprintCallable)
	void ExecutaLogin(FString Usuario,FString senha);
	UFUNCTION(BlueprintCallable)
	void EntraTelaInicial();
	
};
