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

	UFUNCTION(Reliable,Client)
	void AdicionaDadosInstance(int32 IndexJogador);
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	ABaseHudMenuPrincipal* HudChat;

	UPROPERTY(Replicated)
	FString Usuario = "Server";
	UFUNCTION(BlueprintCallable)
	FString GetUsuario() const;
	UFUNCTION(Reliable,Server,BlueprintCallable)
	void SetUsuario(const FString& UsuarioSet);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

};
