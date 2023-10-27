// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// 태어날 때 방향을 정하고싶다.
	// 30% 확률로는 플레이어를 향하는 방향, 나머지 확률로는 앞방향으로 하고싶다.

	// 확률을 구하고싶다.
	int32 randValue = FMath::RandRange(0, 9);
	// 만약 30%라면
	if (randValue < 3)
	{
		//   플레이어 폰을 찾고싶다.
		for (TActorIterator<APlayerPawn> it(GetWorld()); it; ++it)
		{
			APlayerPawn* target = *it;
			if (target == nullptr)
				continue;

			//   플레이폰은 향하는 방향을 구해서 기억하고싶다.
			direction = target->GetActorLocation() - GetActorLocation();
			//   그 방향의 크기를 1로 만들고싶다.
			direction.Normalize();
			break;
		}
	}
	// 그렇지 않다면
	else {
		//  앞방향을 기억 하고싶다.
		direction = GetActorForwardVector();
	}

}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt;
	FVector P0 = GetActorLocation();
	FVector velocity = direction * speed;
	SetActorLocation(P0 + velocity * DeltaTime);
}

