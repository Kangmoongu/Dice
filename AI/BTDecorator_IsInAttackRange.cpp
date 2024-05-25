// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInAttackRange.h"
#include "Controller/DAIController.h"
#include "Character/DNonPlayerCharacter.h"
#include "Character/DCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UBTDecorator_IsInAttackRange::AttackRange(100.f);


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	ADAIController* AIC = Cast<ADAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ADNonPlayerCharacter* NPC = Cast<ADNonPlayerCharacter>(AIC->GetPawn());
		if (true == ::IsValid(NPC))
		{
			ADCharacterBase* TargetPlayerCharacter = Cast<ADCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADAIController::TargetActorKey));
			if (true == ::IsValid(TargetPlayerCharacter))
			{
				return bResult = (NPC->GetDistanceTo(TargetPlayerCharacter) <= AttackRange);
			}
		}
	}
	return bResult=false;
}
