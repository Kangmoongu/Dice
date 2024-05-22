// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DCharacterPlayer.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/DInputConfigData.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TestObject/TestProp.h"
#include "Kismet/KismetSystemLibrary.h"

ADCharacterPlayer::ADCharacterPlayer()
{

    CameraComponent->SetRelativeLocation(FVector(0.f, 100.f, 0.f));

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bDoCollisionTest = true;
    SpringArmComponent->bInheritPitch = true;
    SpringArmComponent->bInheritYaw = true;
    SpringArmComponent->bInheritRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

    GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

    bIsMapOpen = false;
    bIsInteraction = false;

} 

void ADCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (true == ::IsValid(PlayerController))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (true == ::IsValid(Subsystem))
        {
            Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
        }
    }

}

void ADCharacterPlayer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    //SetViewMode(EViewMode::TopView);
    SetViewMode(EViewMode::ShoulderView);

}

void ADCharacterPlayer::SetViewMode(EViewMode InViewMode)
{
    if (CurrentViewMode == InViewMode)
    {
        return;
    }
    CurrentViewMode = InViewMode;

    switch (CurrentViewMode)
    {
    case EViewMode::ShoulderView:


        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->bDoCollisionTest = true;
        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = false;
        SpringArmComponent->TargetArmLength = 400.f;


        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);


        
        break;
    case EViewMode::TopView:

        SpringArmComponent->bUsePawnControlRotation = false;
        SpringArmComponent->bDoCollisionTest = false;
        SpringArmComponent->bInheritPitch = false;
        SpringArmComponent->bInheritYaw = false;
        SpringArmComponent->bInheritRoll = false;
        SpringArmComponent->TargetArmLength = 1400.f;


        SpringArmComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

        break;
    case EViewMode::End:
        break;
    default:
        break;
    }
}



void ADCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->GrapAction, ETriggerEvent::Started, this, &ThisClass::Grap);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->ChangeViewAction, ETriggerEvent::Started, this, &ThisClass::ChangeView);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->OpenMapAction, ETriggerEvent::Started, this, &ThisClass::OpenMap);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->UseHealthPackAction, ETriggerEvent::Started, this, &ThisClass::UseHealthPack);
    EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->InterAction, ETriggerEvent::Started, this, &ThisClass::Interaction);
}

void ADCharacterPlayer::Move(const FInputActionValue& InValue)
{
    FVector2D MovementVector = InValue.Get<FVector2D>();
    ForwardInputValue = MovementVector.X;
    RightInputValue = MovementVector.Y;

    const FRotator CurrentControlRotation = GetController()->GetControlRotation();
    const FRotator CurrentControlRotationYaw(0.f, CurrentControlRotation.Yaw, 0.f);

    FVector ForwardDirection = FRotationMatrix(CurrentControlRotationYaw).GetUnitAxis(EAxis::X);
    FVector RightDirection = FRotationMatrix(CurrentControlRotationYaw).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementVector.X);
    AddMovementInput(RightDirection, MovementVector.Y);
}

void ADCharacterPlayer::Look(const FInputActionValue& InValue)
{
    FVector2D LookAxisVector = InValue.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void ADCharacterPlayer::Grap(const FInputActionValue& InValue)
{
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, this);

    bool bResult = GetWorld()->SweepSingleByChannel(
        HitResult,
        GetActorLocation(),
        GetActorLocation() + GrapRange,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel1,
        FCollisionShape::MakeSphere(GrapRadius),
        Params
    );

    if (true == bResult)
    {
        if (true == ::IsValid(HitResult.GetActor()))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("GrapActor Name: %s"), *HitResult.GetActor()->GetName()));
            //전략적 전투 시작.
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

void ADCharacterPlayer::ChangeView(const FInputActionValue& InValue)
{
    switch (CurrentViewMode)
    {
    case EViewMode::ShoulderView:
        SetViewMode(EViewMode::TopView);
        break;

    case EViewMode::TopView:
        SetViewMode(EViewMode::ShoulderView);
        break;

    case EViewMode::End:
        break;
    default:
        break;
    }
}

void ADCharacterPlayer::Interaction(const FInputActionValue& InValue)
{
    FHitResult InterActionResult;

    FCollisionObjectQueryParams ObjQueryParam;
    ObjQueryParam.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel3);
    if (bool bResult = GetWorld()->LineTraceSingleByObjectType(
        InterActionResult,
        GetActorLocation(),
        GetActorLocation() + InteractionRange,
        ObjQueryParam
    ))
    {
        ATestProp* TestProp = Cast<ATestProp>(InterActionResult.GetActor());
        if (true == ::IsValid(TestProp))
        {
            TestProp->OnInteracted();
        }
    }
    else {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("InteractionFailed!")));
    }
}

void ADCharacterPlayer::OpenMap(const FInputActionValue& InValue)
{
    if (bIsMapOpen == false) 
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("MapOpen")));
        bIsMapOpen = true;
    }
    else {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("MapClose")));
        bIsMapOpen = false;
    }
}

void ADCharacterPlayer::UseHealthPack(const FInputActionValue& InValue)
{
    SetMaxHp(GetMaxHp()+100);
    SetCurrentHp(GetCurrentHp() + 100); //임시로 100회복 설정
    UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("CurrentHp: %d"), GetCurrentHp()));
}



