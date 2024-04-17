// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverWidget.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);
	box->SetBoxExtent(FVector(50));
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));

	// ���� �ε� �õ�
	auto cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Models/Drone/Drone_low.Drone_low'"));

	// ���� ���� �ε� �������� Ȯ���ؼ� �����ߴٸ�
	if (cubeMesh.Succeeded())
	{
		cube->SetStaticMesh(cubeMesh.Object);
		cube->SetRelativeLocation(FVector(0, 0, -50));
		cube->SetRelativeRotation(FRotator(0, -90, 0));
		cube->SetRelativeScale3D(FVector(0.85f));
	}

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

	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(direction, GetActorUpVector());
	SetActorRotation(rot);

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
	if (nullptr == player)
		return;

	// �÷��̾��� ü���� 1 �����ϰ�ʹ�.
	player->OnDamageProcess(1);
	// ���� �÷��̾��� ü���� 0���϶�� �ı��ϰ�ʹ�.
	if (player->hp <= 0)
	{
		// ���װ�
		player->Destroy();

		// ���ӿ��� UI�� ȭ�鿡 ���̰� �ϰ�ʹ�.
		auto ui = CreateWidget(GetWorld(), gameOverUIFactory);
		gameOverUI = Cast<UGameOverWidget>(ui);
		gameOverUI->AddToViewport(99);

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		// �Ͻ����� �ϰ�ʹ�.
		PlayerController->SetPause(true);
		// ���콺 Ŀ�� ���̰� �ϰ�ʹ�.
		PlayerController->SetShowMouseCursor(true);
		// �Է¸�带 UI�� �ϰ�ʹ�.
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	//  ���װ� �ϰ�ʹ�.
	this->Destroy();

	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, GetActorLocation(), GetActorRotation());
}

