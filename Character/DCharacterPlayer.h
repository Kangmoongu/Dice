// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacterBase.h"
#include "InputActionValue.h"
#include "DCharacterPlayer.generated.h"



/**
 * 
 */

UENUM()
enum class EViewMode : uint8
{
    None,
    ShoulderView,
    TopView,
    End
};

UCLASS()
class DICE_API ADCharacterPlayer : public ADCharacterBase
{
	GENERATED_BODY()
	
public:
	ADCharacterPlayer();

	virtual void BeginPlay() override;

    float GetForwardInputValue() const { return ForwardInputValue; }

    float GetRightInputValue() const { return RightInputValue; }

    virtual void PossessedBy(AController* NewController) override;

    void SetViewMode(EViewMode InViewMode);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void Move(const FInputActionValue& InValue);

    void Look(const FInputActionValue& InValue);

    void Grap(const FInputActionValue& InValue);

    void ChangeView(const FInputActionValue& InValue);

    void Interaction(const FInputActionValue& InValue);

    void OpenMap(const FInputActionValue& InValue);

    void UseHealthPack(const FInputActionValue& InValue);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
    TObjectPtr<class UDInputConfigData> PlayerCharacterInputConfigData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
    TObjectPtr<class UInputMappingContext> PlayerCharacterInputMappingContext;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
    float ForwardInputValue;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
    float RightInputValue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = characterstat, Meta = (AllowPrivateAccess = "true"));
    uint8 bIsMapOpen : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = characterstat, Meta = (AllowPrivateAccess = "true"));
    uint8 bIsInteraction : 1;

    EViewMode CurrentViewMode = EViewMode::None;

    FVector DirectionToMove = FVector::ZeroVector;

    float GrapRange = 400.f;

    float GrapRadius = 100.f;

    float InteractionRange = 100.f;





};
