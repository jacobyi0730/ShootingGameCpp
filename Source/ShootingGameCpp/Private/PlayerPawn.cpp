// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// box�� ����� �����ʹ�.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	// �ڽ��� RootComponent�� �ϰ�ʹ�.	
	SetRootComponent(box);

	// cube �ܰ��� �����ʹ�.
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	// �ܰ��� Root�� ���̰�ʹ�.(Attach)
	cube->SetupAttachment(box);

	// arrow�� �����ؼ� ��ġ�ϰ�ʹ�.
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
	// ���� bAutoFire�� true���
	if (true == bAutoFire)
	{
		//   �ð��� �帣�ٰ�
		currentTime += DeltaTime;
		//   ����ð��� �����ð��̵Ǹ�
		if (currentTime > makeTime)
		{
			//   MakeBullet�Լ��� ȣ���ϰ�ʹ�.
			MakeBullet();
			//   ����ð��� 0���� �ʱ�ȭ �ϰ�ʹ�.
			currentTime = 0;
		}
	}
	//=================================================
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// �Է��� �߻��� �� ȣ��� �Լ��� ����ؾ��Ѵ�.

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
	// �ڵ��ѽ�� �ϰ� �ʹ�.
	bAutoFire = true;
	// ����ð��� 0���� �ʱ�ȭ �ϰ� �ʹ�.
	currentTime = 0;
	MakeBullet();
}

void APlayerPawn::ActionFireReleased()
{
	// �ڵ��ѽ�� �׸� �ϰ�ʹ�.
	bAutoFire = false;
}

void APlayerPawn::MakeBullet()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, arrow->GetComponentTransform());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

