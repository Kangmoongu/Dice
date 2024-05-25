// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetSafePatrolPosition.generated.h"

/**
 * 
 */
UCLASS()
class DICE_API UBTTask_GetSafePatrolPosition : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_GetSafePatrolPosition();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
