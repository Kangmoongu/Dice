// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DNonPlayerCharacter.h"
#include "Controller/DAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ADNonPlayerCharacter::ADNonPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ADAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ADNonPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (false == IsPlayerControlled())
    {
        bUseControllerRotationYaw = false;

        GetCharacterMovement()->bOrientRotationToMovement = false;
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

        GetCharacterMovement()->MaxWalkSpeed = 300.f;
    }


}

void ADNonPlayerCharacter::Grap()
{
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, this);

    bool bResult = GetWorld()->SweepSingleByChannel(
        HitResult,
        GetActorLocation(),
        GetActorLocation() + GrapRange * GetActorForwardVector(),
        FQuat::Identity,
        ECollisionChannel::ECC_EngineTraceChannel2,
        FCollisionShape::MakeSphere(GrapRadius),
        Params
    );

    if (true == bResult)
    {
        if (true == ::IsValid(HitResult.GetActor()))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("[NPC] Grap Actor Name: %s"), *HitResult.GetActor()->GetName()));
        }
    }
    
#pragma region CollisionDebugDrawing
    FVector TraceVec = GetActorForwardVector() * GrapRange;
    FVector Center = GetActorLocation() + TraceVec * 0.5f;
    float HalfHeight = GrapRange * 0.5f + GrapRadius;
    FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
    FColor DrawColor = true == bResult ? FColor::Green : FColor::Red;
    float DebugLifeTime = 5.f;

    DrawDebugCapsule(
        GetWorld(),
        Center,
        HalfHeight,
        GrapRadius,
        CapsuleRot,
        DrawColor,
        false,
        DebugLifeTime
    );
#pragma endregion
}