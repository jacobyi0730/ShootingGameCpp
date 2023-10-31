// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "Components/ArrowComponent.h"
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	SetRootComponent(root);
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(root);
	// arrow�� ȸ���ϰ�ʹ�. (Pitch=-90.000000,Yaw=0.000000,Roll=180.000000)
	arrow->SetWorldRotation(FRotator(-90, 0, 180));

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
	// makeTime�� ���ϰ�ʹ�. 
	makeTime = FMath::RandRange(minTime, maxTime);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ð��� �帣�ٰ�
	currentTime += DeltaTime;
	// ���� ����ð��� �����ð��� �ʰ��ߴٸ� 
	if (currentTime > makeTime)
	{
		//		����ð��� 0���� �ʱ�ȭ �ϰ�ʹ�.
		currentTime = 0;
		//		�� ���忡�� ���� ���� Arrow��ġ�� ��ġ�ϰ� �ʹ�
		GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, arrow->GetComponentTransform());

		// makeTime�� ���ϰ�ʹ�. 
		makeTime = FMath::RandRange(minTime, maxTime);
	}
}

