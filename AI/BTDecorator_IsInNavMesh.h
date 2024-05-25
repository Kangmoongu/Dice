// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInNavMesh.generated.h"

/**
 * 
 */
UCLASS()
class DICE_API UBTDecorator_IsInNavMesh : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsInNavMesh();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
