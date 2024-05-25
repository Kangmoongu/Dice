// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DAIController.generated.h"

/**
 * 
 */
UCLASS()
class DICE_API ADAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADAIController();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BeginAI(APawn* InPawn);

	void EndAI();

public:
	static const float PatrolRadius;

	static const FName StartPatrolPositionKey;

	static const FName EndPatrolPositionKey;

	static const FName SafePatrolPositionKey;

	static const FName TargetActorKey;

	static const FName bIsNavMeshInRangeKey;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBlackboardData> BlackboardDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
