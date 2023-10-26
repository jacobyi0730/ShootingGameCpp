// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// box의 모양을 만들고싶다.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	// 박스를 RootComponent로 하고싶다.	
	SetRootComponent(box);

	// cube 외관을 만들고싶다.
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	// 외관을 Root에 붙이고싶다.(Attach)
	cube->SetupAttachment(box);

	// arrow를 생성해서 배치하고싶다.
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(box);
	// Loc (X=0.000000,Y=0.000000,Z=70.000000)
	arrow->SetRelativeLocation(FVector(0, 0, 70));
	// Rot (Pitch=90.000000,Yaw=0.000000,Roll=0.000000)
	arrow->SetRelativeRotation(FRotator(90, 0, 0));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move ========================================
	{
		// P = P0 + vt
		FVector P0 = GetActorLocation();
		FVector dir = GetActorUpVector() * v + GetActorRightVector() * h;
		dir.Normalize();
		FVector velocity = dir * speed;
		SetActorLocation(P0 + velocity * DeltaTime);
	}
	//=================================================

	//AutoFire =======================================
	// 만약 bAutoFire가 true라면
	if (true == bAutoFire)
	{
		//   시간이 흐르다가
		currentTime += DeltaTime;
		//   현재시간이 생성시간이되면
		if (currentTime > makeTime)
		{
			//   MakeBullet함수를 호출하고싶다.
			MakeBullet();
			//   현재시간을 0으로 초기화 하고싶다.
			currentTime = 0;
		}
	}
	//=================================================
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 입력이 발생할 때 호출될 함수를 등록해야한다.

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::AxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::AxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerPawn::ActionFirePressed);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &APlayerPawn::ActionFireReleased);
}

void APlayerPawn::AxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::AxisVertical(float value)
{
	v = value;
}

void APlayerPawn::ActionFirePressed()
{
	// 자동총쏘기 하고 싶다.
	bAutoFire = true;
	// 현재시간을 0으로 초기화 하고 싶다.
	currentTime = 0;
	MakeBullet();
}

void APlayerPawn::ActionFireReleased()
{
	// 자동총쏘기 그만 하고싶다.
	bAutoFire = false;
}

void APlayerPawn::MakeBullet()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, arrow->GetComponentTransform());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

