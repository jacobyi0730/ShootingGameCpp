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

	//UE_LOG(LogTemp, Warning, TEXT("안녕 월드야!"));
	// number
	//UE_LOG(LogTemp, Warning, TEXT("%d"), number);
	//UE_LOG(LogTemp, Warning, TEXT("%.3f"), fNumber);

	//UE_LOG(LogTemp, Warning, TEXT("bool is false : %d"), false);

	//UE_LOG(LogTemp, Warning, TEXT("bool is true : %d"), true);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *myName);
	if (myName.Equals(TEXT("KTJ")))
	{
		UE_LOG(LogTemp, Warning, TEXT("호주에 별장 사고싶다."));
	}
	else if (myName.Equals(TEXT("LSK")))
	{
		UE_LOG(LogTemp, Warning, TEXT("벌금내고 싶다."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("맥북 사고싶다"));
	}

	// 조건문
	// 만약 myName이 KTJ이라면 호주에 별장 사고싶다.
	// 그렇지않고 myName LSK이라면 벌금내고싶다.
	// 이도저도 아니라면 맥북사고싶다.
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

