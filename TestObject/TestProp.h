// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestProp.generated.h"


UCLASS()
class DICE_API ATestProp : public AActor
{

	GENERATED_BODY()
	
public:	
	ATestProp();

	void OnInteracted();
protected:



	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class USphereComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
