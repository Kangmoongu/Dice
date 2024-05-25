// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetSafePatrolPosition.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Circle/MySphere.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetSafePatrolPosition::UBTTask_GetSafePatrolPosition()
{
    NodeName = TEXT("GetSafePatrolPosition"); // Behavior Tree에 보일 노드 이름.
}

EBTNodeResult::Type UBTTask_GetSafePatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
    FNavLocation SafePatrolLocation;
    
    if (true == NavigationSystem->ProjectPointToNavigation(StartPatrolPosition, SafePatrolLocation, FVector(5000, 5000, 5000)))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(ADAIController::SafePatrolPositionKey, SafePatrolLocation.Location);
        return Result = EBTNodeResult::Succeeded;
    }

    return Result;
}
