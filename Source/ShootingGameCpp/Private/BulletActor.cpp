// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체와 외관을 생성하고싶다. 충돌체를 Root로하고 외관을 Root에 붙이고싶다.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
	// 외관의 크기과 충돌체의 크기를 설정하고싶다.
	cube->SetRelativeScale3D(FVector(0.75f, 0.25f, 1));
	box->SetBoxExtent(FVector(37.5f, 12.5f, 50));
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 앞 방향으로 계속 이동하고싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector v = GetActorForwardVector() * speed;
	SetActorLocation(P0 + v * DeltaTime);
}

