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

	// 파일 로딩 시도
	auto cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Models/Drone/Drone_low.Drone_low'"));

	// 만약 파일 로딩 성공여부 확인해서 성공했다면
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

	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(direction, GetActorUpVector());
	SetActorRotation(rot);

	// box에게 충돌했으면 나도 알려줘라고 하고싶다.
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
	// 상대방이 Player라면
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (nullptr == player)
		return;

	// 플레이어의 체력을 1 감소하고싶다.
	player->OnDamageProcess(1);
	// 만약 플레이어의 체력이 0이하라면 파괴하고싶다.
	if (player->hp <= 0)
	{
		// 너죽고
		player->Destroy();

		// 게임오버 UI를 화면에 보이게 하고싶다.
		auto ui = CreateWidget(GetWorld(), gameOverUIFactory);
		gameOverUI = Cast<UGameOverWidget>(ui);
		gameOverUI->AddToViewport(99);

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		// 일시정지 하고싶다.
		PlayerController->SetPause(true);
		// 마우스 커서 보이게 하고싶다.
		PlayerController->SetShowMouseCursor(true);
		// 입력모드를 UI만 하고싶다.
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	//  나죽고 하고싶다.
	this->Destroy();

	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, GetActorLocation(), GetActorRotation());
}

