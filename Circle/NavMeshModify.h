// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavMeshModify.generated.h"

UCLASS()
class DICE_API ANavMeshModify : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavMeshModify();

	void MeshTimer(AMySphere* SphereCast);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	TObjectPtr<class ANavMeshBoundsVolume> NavMesh;

	UPROPERTY()
	TObjectPtr<class UNavigationSystemV1> NavSys;
};
