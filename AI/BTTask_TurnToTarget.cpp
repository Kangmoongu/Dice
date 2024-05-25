// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"
#include "Character/DCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
    NodeName = TEXT("TurnToTargetActor");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ADAIController* AIC = Cast<ADAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            if (ADCharacterBase* TargetPC = Cast<ADCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIC->TargetActorKey)))
            {
                FVector LookVector = TargetPC->GetActorLocation() - NPC->GetActorLocation();
                LookVector.Z = 0.f;
                FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
                NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.f));

                return Result = EBTNodeResult::Succeeded;
            }
        }
    }

    return Result = EBTNodeResult::Failed;
}
