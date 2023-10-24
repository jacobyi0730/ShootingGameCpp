// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"


// Sets default values
ACodingActor::ACodingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();

	//	배열에 10개 항목을 넣는데 1이상 2이하값을 랜덤으로 누적해서 넣기
	//float sum = 0;
	//for (int i = 0; i < 10; i++)
	//{
	//	sum += FMath::RandRange(1.0f, 2.0f);
	//	notes.Add(sum);
	//	//UE_LOG(LogTemp, Warning, TEXT("%.2f"), sum);
	//}

	/*int result = MyAdd(10, 20);
	UE_LOG(LogTemp, Warning, TEXT("%d"), result);*/


}



// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//// 1. tick에서 시간이 흐르다가 
	//currentTime += DeltaTime;
	//// 2. noteIndex가 배열크기보다 작고 배열의 현재 인덱스 항목의 시간만큼 시간이 흘렀다면
	//if (noteIndex < notes.Num() && currentTime >= notes[noteIndex])
	//{
	//	// 3. 배열의 인덱스와 값을 출력하고 인덱스값을 1증가
	//	UE_LOG(LogTemp, Warning, TEXT("index : %d, time : %.2f"), noteIndex, notes[noteIndex]);
	//
	//	noteIndex++;
	//}
}

// 함수의 정의/구현
int ACodingActor::MyAdd(int a, int b)
{
	return a + b;
}

int ACodingActor::MyAdd2(int a, int b)
{
	return a + b;
}

int ACodingActor::MyAdd4_Implementation(int a, int b)
{
	return a + b;
}


