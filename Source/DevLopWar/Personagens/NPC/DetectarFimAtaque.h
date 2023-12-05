//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DetectarFimAtaque.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UDetectarFimAtaque : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation) override;
};
