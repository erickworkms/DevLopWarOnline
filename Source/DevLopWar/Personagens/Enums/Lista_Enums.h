#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum TipoEstado
{
	NoChaoAndando UMETA(DisplayName = "NoChao"),
	Caindo UMETA(DisplayName = "Caindo"),
	Voando UMETA(DisplayName = "Voando"),
	Preso UMETA(DisplayName = "Preso")
};

UENUM(BlueprintType)
enum TipoAcao
{
	Atacar UMETA(DisplayName = "Atacar"),
	Pular UMETA(DisplayName = "Pular"),
	TomarDano UMETA(DisplayName = "TomarDano"),
	Queda UMETA(DisplayName = "Queda"),
	Morto UMETA(DisplayName = "Morto"),
	Nada UMETA(DisplayName = "Nada")
};

UENUM(BlueprintType)
enum TipoPersonagem
{
	Chefe UMETA(DisplayName = "Chefe"),
	Senior UMETA(DisplayName = "Senior"),
	Pleno UMETA(DisplayName = "Pleno"),
	Estagiario UMETA(DisplayName = "Estagiario"),
	Nenhum UMETA(DisplayName = "Nenhum")
};

UENUM(BlueprintType)
enum TipoIAEstado
{
	Perseguir_NPC UMETA(DisplayName = "Perseguindo"),
	Patrulha_NPC UMETA(DisplayName = "Patrulhando"),
	Ocioso_NPC UMETA(DisplayName = "Ocioso"),
	Queda_NPC UMETA(DisplayName = "Queda"),
	TomarDano_NPC UMETA(DisplayName = "TomarDano"),
	Morto_NPC UMETA(DisplayName = "Morto"),
	Descansar_NPC UMETA(DisplayName = "Descansando"),
	Nada_NPC UMETA(DisplayName = "Nada")
};