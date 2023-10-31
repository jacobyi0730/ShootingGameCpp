// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);

	box->SetGenerateOverlapEvents(true);

	box->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// �¾ �� ������ ���ϰ�ʹ�.
	// 30% Ȯ���δ� �÷��̾ ���ϴ� ����, ������ Ȯ���δ� �չ������� �ϰ�ʹ�.

	// Ȯ���� ���ϰ�ʹ�.
	int32 randValue = FMath::RandRange(0, 9);
	// ���� 30%���
	if (randValue < 3)
	{
		//   �÷��̾� ���� ã��ʹ�.
		for (TActorIterator<APlayerPawn> it(GetWorld()); it; ++it)
		{
			APlayerPawn* target = *it;
			if (target == nullptr)
				continue;

			//   �÷������� ���ϴ� ������ ���ؼ� ����ϰ�ʹ�.
			direction = target->GetActorLocation() - GetActorLocation();
			//   �� ������ ũ�⸦ 1�� �����ʹ�.
			direction.Normalize();
			break;
		}
	}
	// �׷��� �ʴٸ�
	else {
		//  �չ����� ��� �ϰ�ʹ�.
		direction = GetActorForwardVector();
	}

	// box���� �浹������ ���� �˷����� �ϰ�ʹ�.
	box->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompBeginOverlap);
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

void AEnemyActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ������ Player���
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player)
	{
		// ���װ�
		player->Destroy();
		//  ���װ� �ϰ�ʹ�.
		this->Destroy();

		UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);
	}
}

