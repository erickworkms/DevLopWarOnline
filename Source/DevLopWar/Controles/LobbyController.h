//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Huds/BaseHudMenuPrincipal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyController();
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void EnviarMensagemServer(const FString& nome,const FString& mensagem);

	UFUNCTION(Reliable,Client)
	void EnviarMensagemCliente(const FString& nome,const FString& mensagem);
	
	UFUNCTION(Reliable,Client)
	void VerEntradaLogin(const TArray<FString>& JogadoresSalaNome);

	UPROPERTY(Replicated,BlueprintReadWrite)
	ABaseHudMenuPrincipal* HudChat;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

};
