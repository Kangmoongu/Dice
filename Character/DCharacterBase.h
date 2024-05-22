// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacterBase.generated.h"

UCLASS()
class DICE_API ADCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADCharacterBase();

protected:
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category= camera ,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category= camera,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

public:	
	void SetMaxHp(const float& InMaxHp)  { MaxHp = InMaxHp; }
	float GetMaxHp() const { return MaxHp; }

	void SetCurrentHp(const float& InCurrentHp) { CurrentHp = InCurrentHp; }
	float GetCurrentHp() const { return CurrentHp; }

	bool IsDead() const { return bIsDead; }
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = characterstat, Meta = (AllowPrivateAccess = "true"));
	float MaxHp=200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = characterstat, Meta = (AllowPrivateAccess = "true"));
	float CurrentHp=200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = characterstat, Meta = (AllowPrivateAccess = "true"));
	uint8 bIsDead : 1;



	

};
