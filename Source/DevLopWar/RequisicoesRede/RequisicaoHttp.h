//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "RequisicaoHttp.generated.h"

UCLASS()
class DEVLOPWAR_API URequisicaoHttp : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	static void EnviaRequisicaoHttpGetHeader(const FString& Url, const FString& Verb,UObject* CallbackTarget, FName CallbackFunction,const FString& Token);
	
	UFUNCTION()
	static void EnviaRequisicaoHttpJsonHeader(const FString& Url, const FString& Verb, const FString& Content, UObject* CallbackTarget, FName CallbackFunction,const FString& Token);
	
	UFUNCTION()
	static void EnviaRequisicaoHttpJson(const FString& Url, const FString& Verb, const FString& Content, UObject* CallbackTarget, FName CallbackFunction);

	UFUNCTION()
	static void EnviaRequisicaoHttpParam(const FString& Url, const FString& Verb, const FString& Content, UObject* CallbackTarget, FName CallbackFunction);

private:
	static void OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess, UObject* CallbackTarget, FName CallbackFunction);
};
