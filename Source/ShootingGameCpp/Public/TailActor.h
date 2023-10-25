// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TailActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API ATailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// [�ʿ���]
	// - �ڽ�������Ʈ
	UPROPERTY(EditAnywhere)
	class UBoxComponent* box;
	// - staticMesh������Ʈ
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;
	// - �ӵ�
	UPROPERTY(EditAnywhere)
	float speed = 450;
	// - ������
	UPROPERTY(EditAnywhere)
	AActor* targetActor;
	
};
