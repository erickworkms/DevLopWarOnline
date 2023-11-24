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
		UFunction* Function = CallbackTarget->FindFunction(CallbackFunction);
		CallbackTarget->ProcessEvent(Function, &CallbackParams);
	}
}
