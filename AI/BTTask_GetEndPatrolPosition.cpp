// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetEndPatrolPosition.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetEndPatrolPosition::UBTTask_GetEndPatrolPosition()
{
    NodeName = TEXT("GetEndPatrolPosition"); // Behavior Tree에 보일 노드 이름.
}

EBTNodeResult::Type UBTTask_GetEndPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if (EBTNodeResult::Failed == Result)
    {
        return Result;
    }

    ADAIController* AIController = Cast<ADAIController>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController"));


    ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC"));


    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(NPC->GetWorld());
	checkf(IsValid(NavigationSystem) == true, TEXT("Invalid NavigationSystem"));


    FVector StartPatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ADAIController::StartPatrolPositionKey);
    FNavLocation EndPatrolLocation;
    if (true == NavigationSystem->GetRandomPointInNavigableRadius(StartPatrolPosition, AIController->PatrolRadius, EndPatrolLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(ADAIController::EndPatrolPositionKey, EndPatrolLocation.Location);
        return Result = EBTNodeResult::Succeeded;
    }

    return Result;
}
