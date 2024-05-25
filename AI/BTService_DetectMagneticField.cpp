// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectMagneticField.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/DCharacterBase.h"
#include "NavigationSystem.h"


UBTService_DetectMagneticField::UBTService_DetectMagneticField()
{
	NodeName = TEXT("DetectMagneticField");
	Interval = 1.f;
}

void UBTService_DetectMagneticField::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ADAIController* AIController = Cast<ADAIController>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController"));


    ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC"));


    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(NPC->GetWorld());
    checkf(IsValid(NavigationSystem) == true, TEXT("Invalid NavigationSystem"));

    FVector StartPatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ADAIController::StartPatrolPositionKey);

    FNavLocation NavMesh;
    FNavLocation SafePatrolLocation;

    bool bIsNavMeshFounded = NavigationSystem->ProjectPointToNavigation(StartPatrolPosition, NavMesh);
    if (!bIsNavMeshFounded)
    {
        NavigationSystem->ProjectPointToNavigation(StartPatrolPosition, SafePatrolLocation, FVector(5000.f, 5000.f, 5000.f));
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADAIController::bIsNavMeshInRangeKey, false);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(ADAIController::SafePatrolPositionKey, SafePatrolLocation.Location);
        NPC->SetActorLocation(SafePatrolLocation.Location);
    }
    else {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADAIController::bIsNavMeshInRangeKey, true);

    }
}
