// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject/TestProp.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/DCharacterPlayer.h"


ATestProp::ATestProp()
{
	InteractionBox = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	InteractionBox->InitSphereRadius(300.0f);
	InteractionBox->SetCollisionProfileName(TEXT("Interactionable"));
	RootComponent = InteractionBox;

	InteractionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreasureBox"));
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(SphereVisualAsset.Object);
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		Mesh->SetWorldScale3D(FVector(0.8f));
	}

}

void ATestProp::BeginPlay()
{
	Super::BeginPlay();
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ATestProp::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ATestProp::OnOverlapEnd);
}

void ATestProp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ATestProp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ADCharacterPlayer* Player = Cast<ADCharacterPlayer>(OtherActor);
	if (true == ::IsValid(Player))
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("can interaction!")));
	}
}

void ATestProp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADCharacterPlayer* Player = Cast<ADCharacterPlayer>(OtherActor);
	if (true == ::IsValid(Player))
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("can't interaction!")));

	}
}

void ATestProp::OnInteracted()
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("interacted!")));

}


