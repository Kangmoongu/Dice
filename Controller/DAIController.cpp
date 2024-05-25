// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

const float ADAIController::PatrolRadius(500.f);
const FName ADAIController::StartPatrolPositionKey(TEXT("StartPatrolPosition"));
const FName ADAIController::EndPatrolPositionKey(TEXT("EndPatrolPosition"));
const FName ADAIController::SafePatrolPositionKey(TEXT("SafePatrolPosition"));
const FName ADAIController::TargetActorKey(TEXT("TargetActor"));
const FName ADAIController::bIsNavMeshInRangeKey(TEXT("bIsNavMeshInRange"));



ADAIController::ADAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BrainComponent"));
}

void ADAIController::BeginAI(APawn* InPawn)
{
    UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Blackboard);
    if (true == ::IsValid(BlackboardComponent))
    {
        if (true == UseBlackboard(BlackboardDataAsset, BlackboardComponent))
        {
            bool bRunSucceeded = RunBehaviorTree(BehaviorTree);
            ensure(true == bRunSucceeded);
            BlackboardComponent->SetValueAsVector(StartPatrolPositionKey, InPawn->GetActorLocation());
        }
    }
}

void ADAIController::EndAI()
{
    UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (true == ::IsValid(BehaviorTreeComponent))
    {
        BehaviorTreeComponent->StopTree();
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("EndAI() has been called.")));
    }
}

void ADAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* ControlledPawn = GetPawn();
    if (true == ::IsValid(ControlledPawn))
    {
        BeginAI(ControlledPawn);
    }
}

void ADAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

    EndAI();

    Super::EndPlay(EndPlayReason);

}