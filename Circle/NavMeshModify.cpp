// Fill out your copyright notice in the Description page of Project Settings.


#include "Circle/NavMeshModify.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "MySphere.h"

// Sets default values
ANavMeshModify::ANavMeshModify()
{

}

void ANavMeshModify::MeshTimer(AMySphere* SphereCast)
{
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this,SphereCast]()->void
        {
            FVector SphereScale = SphereCast->GetActorScale3D();
            FVector Field = SphereScale * 100;
            FBoxSphereBounds Bounds2(NavMesh->GetActorLocation(), Field, Field.X/2);
            NavMesh->GetRootComponent()->Bounds = Bounds2;
            NavSys->OnNavigationBoundsUpdated(NavMesh);
        }, 10.f, true);
}

// Called when the game starts or when spawned
void ANavMeshModify::BeginPlay()
{
	Super::BeginPlay();

    FPlatformProcess::Sleep(11);
    FVector SphereLocation;
    TArray<AActor*> ActorsToFind;
    if (UWorld* world = GetWorld())
    {
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySphere::StaticClass(), ActorsToFind);
    }
    for (AActor* SphereActor : ActorsToFind)
    {
        AMySphere* SphereCast = Cast<AMySphere>(SphereActor);
        if (SphereCast)
        {
             SphereLocation = SphereCast->GetActorLocation();
        }
        NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        NavMesh = GetWorld()->SpawnActor<ANavMeshBoundsVolume>(ANavMeshBoundsVolume::StaticClass(), SphereLocation, FRotator::ZeroRotator);
        NavMesh->SetReplicates(true);
        FBoxSphereBounds Bounds1(NavMesh->GetActorLocation(), FVector(10000.f, 10000.f, 10000.f), 5000.f);
        NavMesh->GetRootComponent()->Bounds = Bounds1;
        NavSys->OnNavigationBoundsUpdated(NavMesh);
        MeshTimer(SphereCast);
    }

}


