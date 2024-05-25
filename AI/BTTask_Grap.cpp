// BTTask_Grap.cpp


#include "AI/BTTask_Grap.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"

UBTTask_Grap::UBTTask_Grap()
{
    bNotifyTick = true;
}

void UBTTask_Grap::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ADAIController* AIC = Cast<ADAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            if (false == NPC->IsNowGrap())
            {
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            }
        }
    }
}

EBTNodeResult::Type UBTTask_Grap::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ADAIController* AIC = Cast<ADAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            NPC->Grap();
        }
    }

    return EBTNodeResult::InProgress;
}