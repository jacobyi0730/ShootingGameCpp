// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

ATailActor::ATailActor()
{
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();
	// ���� target�� nullptr�̶�� target�� �÷��̾����� ã�Ƽ� �־��ְ�ʹ�.

	// UGameplayStatics::GetPlayerPawn
	// UGameplayStatics::GetActorOfClass
	// UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	// GetWorld()->GetFirstPlayerController()->GetPawn()
	if (targetActor == nullptr)
	{
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// target - me �� ������ �����
	FVector dir = targetActor->GetActorLocation() - this->GetActorLocation();
	dir.Normalize();
	// �� �������� �̵��ϰ�ʹ�.
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime);

}

