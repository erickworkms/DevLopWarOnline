// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectarFimAtaque.h"

#include "NPC_Base.h"

void UDetectarFimAtaque::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());
	if(IsValid(NPC))
	{
		NPC->PodeMovimentar = true;
		NPC->Acao = Nada;
	}
}
