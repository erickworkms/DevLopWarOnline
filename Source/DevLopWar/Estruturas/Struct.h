#pragma once

#include "Struct.generated.h"

USTRUCT(BlueprintType)
struct FHttpResponseData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	int32 StatusCode;

	UPROPERTY(BlueprintReadOnly)
	FString ResponseContent;
};


USTRUCT(BlueprintType)
struct FCallbackParametros
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool conectou;

	UPROPERTY(BlueprintReadOnly)
	FHttpResponseData RespostaDados;
};

USTRUCT(BlueprintType)
struct FDadosUsuario
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString nome;

	UPROPERTY(BlueprintReadWrite)
	FString dataNascimento;

	UPROPERTY(BlueprintReadWrite)
	FString email;

	UPROPERTY(BlueprintReadWrite)
	FString usuario;

	UPROPERTY(BlueprintReadWrite)
	FString senha;
};
UENUM(BlueprintType)
enum class ETime : uint8
{
	Clientes,
	Agil,
	Cascade,
	Nenhum
};
UENUM(BlueprintType)
enum class EFase : uint8
{
	Fase1,
	Fase2,
	Fase3,
};
USTRUCT(BlueprintType)
struct FInformacaoJogador
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	FString Nome;

	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	ETime Time;
};
USTRUCT(BlueprintType)
struct FInformacaoJogadorGameplay
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	int32 NumZumbiesMortos;
	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	int32 NumJogadoresMortos;
	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	int32 NumMortes;
	UPROPERTY(BlueprintReadWrite, Category = "Jogador")
	ETime TimeEscolhido;
};
USTRUCT(BlueprintType)
struct FSala
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString idSala;
	
	UPROPERTY(BlueprintReadWrite)
	FString NomeSala;

	UPROPERTY(BlueprintReadWrite)
	FString MapaIndex;

	UPROPERTY(BlueprintReadWrite)
	FString Cenario;
	
	UPROPERTY(BlueprintReadWrite)
	FString IP;

	UPROPERTY(BlueprintReadWrite)
	FString Lan;

	UPROPERTY(BlueprintReadWrite)
	FString NumeroJogadoresAtivos;

	UPROPERTY(BlueprintReadWrite)
	FString NumeroJogadoresTotais;

	UPROPERTY(BlueprintReadWrite)
	FString ServidorDedicado;
};

