//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projetil.generated.h"

UCLASS()
class DEVLOPWAR_API AProjetil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjetil();
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	AActor* DonoProjetil;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UProjectileMovementComponent* Projetil;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UStaticMeshComponent* ProjetilMesh;
	
	UFUNCTION(Reliable,Server)
	void DanoAtaqueProjetil(AActor* InimigoDetectado);

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(IsValid(DonoProjetil))
		{
			if(InimigoDetectado != this && InimigoDetectado != DonoProjetil)
			{
				DanoAtaqueProjetil(InimigoDetectado);
			}
		}
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
