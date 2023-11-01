// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABulletActor::ABulletActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹ü�� �ܰ��� �����ϰ�ʹ�. �浹ü�� Root���ϰ� �ܰ��� Root�� ���̰�ʹ�.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
	// �ܰ��� ũ��� �浹ü�� ũ�⸦ �����ϰ�ʹ�.
	cube->SetRelativeScale3D(FVector(0.75f, 0.25f, 1));
	box->SetBoxExtent(FVector(37.5f, 12.5f, 50));

	// �浹������ �ϰ�ʹ�.
	box->SetGenerateOverlapEvents(true);
	
	box->SetCollisionProfileName(TEXT("Bullet"));

	//box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//box->SetCollisionObjectType(ECC_GameTraceChannel2);
	//box->SetCollisionResponseToAllChannels(ECR_Ignore);
	//box->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);	// Enemy
	//box->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);	// DestroyZone

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	// box���� �浹�� ���� ������ �˷� �޶�� �ϰ� �ʹ�.
	box->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBoxCompBeginOverlap);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �� �������� ��� �̵��ϰ�ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector v = GetActorForwardVector() * speed;
	SetActorLocation(P0 + v * DeltaTime);
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//// �ε��� ��밡 AEnemyActor���
	//if (OtherActor->IsA<AEnemyActor>())
	//{
	//	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	//	// ���װ�
	//	enemy->Destroy();
	//	// ���װ� �ϰ�ʹ�.
	//	this->Destroy();
	//}
}

void ABulletActor::Destroyed()
{
	// �Ѿ��� ������ �ı��Ǳ� ������ ȣ��Ǵ� �Լ�.
}

void ABulletActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ε��� ��밡 AEnemyActor���
	if (OtherActor->IsA<AEnemyActor>())
	{
		AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
		// ���װ�
		enemy->Destroy();
		// ���װ� �ϰ�ʹ�.
		this->Destroy();

		UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, enemy->GetActorTransform());

	}
}
