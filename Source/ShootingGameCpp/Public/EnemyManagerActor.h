// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �ð��� �帣�ٰ� �����ð��� �Ǹ� �� ���忡�� ���� ���� Arrow��ġ�� ��ġ�ϰ� �ʹ�.
	// �����ð��� �Ź� �ٲٰ� �ʹ�. �ּڰ�, �ִ밪
	// �Ӽ�(�ɹ�����)
	// ����ð�, �����ð�, �� ����, Arrow
	float currentTime;
	float makeTime = 2;
	// makeTime�� ���ϰ�ʹ�. 
	// 1. �¾ ��
	// 2. Enemy�� Spawn�ϰ��� 
	UPROPERTY(EditAnywhere)
	float minTime = 1;

	UPROPERTY(EditAnywhere)
	float maxTime = 3;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemyFactory;

	UPROPERTY(EditAnywhere)
	class USceneComponent* root;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* arrow;


};
