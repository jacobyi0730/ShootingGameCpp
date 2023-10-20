// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API ACodingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACodingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// (Edit / Visible) + (Anywhere / DefaultsOnly / InstanceOnly)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar)
	int number = 10; // 4byte 정수형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar)
	float fNumber = 10.0f; // 실수형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar)
	bool bReady = false; // 논리형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar)
	FString myName = TEXT("KTJ"); // 문자열
};
