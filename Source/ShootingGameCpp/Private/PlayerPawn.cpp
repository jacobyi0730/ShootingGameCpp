// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"

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
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector dir = GetActorUpVector() * v + GetActorRightVector() * h;
	dir.Normalize();
	FVector velocity = dir * speed;
	SetActorLocation(P0 + velocity * DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// �Է��� �߻��� �� ȣ��� �Լ��� ����ؾ��Ѵ�.

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::AxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::AxisVertical);
}

void APlayerPawn::AxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::AxisVertical(float value)
{
	v = value;
}

