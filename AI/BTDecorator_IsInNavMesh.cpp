// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInNavMesh.h"
#include "Controller/DAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInNavMesh::UBTDecorator_IsInNavMesh()
{
	NodeName = TEXT("IsInNavMesh");
}

bool UBTDecorator_IsInNavMesh::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(ADAIController::bIsNavMeshInRangeKey))
		return bResult = true;
	return bResult=false;
}
