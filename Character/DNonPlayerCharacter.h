// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacterBase.h"
#include "DNonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DICE_API ADNonPlayerCharacter : public ADCharacterBase
{
	GENERATED_BODY()
	friend class UBTTask_Grap;


public:
	ADNonPlayerCharacter();

	virtual void BeginPlay() override;

	bool IsNowGrap() const { return bIsGrap; }

private:
	void Grap();

	float GrapRange = 400.f;
	float GrapRadius = 100.f;
	bool bIsGrap = false;

};
