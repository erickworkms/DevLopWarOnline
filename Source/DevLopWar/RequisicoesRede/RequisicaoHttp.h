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
	static void EnviaRequisicaoHttpJson(const FString& Url, const FString& Verb, const FString& Content, UObject* CallbackTarget, FName CallbackFunction);

	UFUNCTION()
	static void EnviaRequisicaoHttpParam(const FString& Url, const FString& Verb, const FString& Content, UObject* CallbackTarget, FName CallbackFunction);

private:
	static void OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess, UObject* CallbackTarget, FName CallbackFunction);
};
