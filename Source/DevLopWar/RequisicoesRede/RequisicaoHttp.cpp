//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "RequisicaoHttp.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "DevLopWar/Estruturas/Struct.h"



void URequisicaoHttp::EnviaRequisicaoHttpJson(const FString& Url, const FString& Verb, const FString& Content,
                                              UObject* CallbackTarget, FName CallbackFunction)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Requisicao = FHttpModule::Get().CreateRequest();
	Requisicao->SetURL(Url);
	Requisicao->SetVerb(Verb);
	Requisicao->SetContentAsString(Content);
	Requisicao->SetHeader("Content-Type", "application/json");
	Requisicao->OnProcessRequestComplete().BindStatic(&URequisicaoHttp::OnHttpRequestComplete, CallbackTarget,
	                                                  CallbackFunction);
	Requisicao->ProcessRequest();
}

void URequisicaoHttp::EnviaRequisicaoHttpGetHeader(const FString& Url, const FString& Verb, UObject* CallbackTarget,
	FName CallbackFunction, const FString& Token)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Requisicao = FHttpModule::Get().CreateRequest();
	Requisicao->SetURL(Url);
	Requisicao->SetVerb(Verb);
	Requisicao->SetHeader("Authorization", Token);
	Requisicao->OnProcessRequestComplete().BindStatic(&URequisicaoHttp::OnHttpRequestComplete, CallbackTarget,
													  CallbackFunction);
	Requisicao->ProcessRequest();
}

void URequisicaoHttp::EnviaRequisicaoHttpJsonHeader(const FString& Url, const FString& Verb, const FString& Content,
                                                    UObject* CallbackTarget, FName CallbackFunction,const FString& Token)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Requisicao = FHttpModule::Get().CreateRequest();
	Requisicao->SetURL(Url);
	Requisicao->SetVerb(Verb);
	Requisicao->SetHeader("Content-Type", "application/json");
	Requisicao->SetHeader("Authorization", Token);
	Requisicao->SetContentAsString(Content);
	Requisicao->OnProcessRequestComplete().BindStatic(&URequisicaoHttp::OnHttpRequestComplete, CallbackTarget,
													  CallbackFunction);
	Requisicao->ProcessRequest();
}
void URequisicaoHttp::EnviaRequisicaoHttpParam(const FString& Url, const FString& Verb, const FString& Content,
                                               UObject* CallbackTarget, FName CallbackFunction)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Requisicao = FHttpModule::Get().CreateRequest();
	Requisicao->SetURL(Url);
	Requisicao->SetVerb(Verb);
	Requisicao->SetContentAsString(Content);
	Requisicao->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	Requisicao->OnProcessRequestComplete().BindStatic(&URequisicaoHttp::OnHttpRequestComplete, CallbackTarget,
	                                                  CallbackFunction);

	Requisicao->ProcessRequest();
}

void URequisicaoHttp::OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool conectou,
                                            UObject* CallbackTarget, FName CallbackFunction)
{
	if (Response.IsValid())
	{
		FHttpResponseData ResponseData;
		FCallbackParametros CallbackParams;
		ResponseData.StatusCode = Response->GetResponseCode();
		ResponseData.ResponseContent = Response->GetContentAsString();
		CallbackParams.conectou = conectou;
		CallbackParams.RespostaDados = ResponseData;
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,ResponseData.ResponseContent);
		UFunction* Function = CallbackTarget->FindFunction(CallbackFunction);
		CallbackTarget->ProcessEvent(Function, &CallbackParams);
	}
}
