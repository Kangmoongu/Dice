// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectMagneticField.generated.h"

/**
 * 
 */
UCLASS()
class DICE_API UBTService_DetectMagneticField : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_DetectMagneticField();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
