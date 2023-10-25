// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"

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

