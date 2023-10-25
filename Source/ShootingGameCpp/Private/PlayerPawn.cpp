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
	cube->SetupAttachment(RootComponent);

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

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

