// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ADCharacterBase::ADCharacterBase()
{
    //CameraSection - CapsuleSize Setting
    float CharacterHalfHeight = 96.f;
    float CharacterRadius = 42.f;
    GetCapsuleComponent()->InitCapsuleSize(CharacterRadius, CharacterHalfHeight);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("DCharacter"));

    //CameraSection - Subobject Create
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.f;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
    CameraComponent->bUsePawnControlRotation = false;

    //Movement - Movement Setting
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    //Mesh - Mesh Setting
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

    bIsDead = false;


    


    

}



