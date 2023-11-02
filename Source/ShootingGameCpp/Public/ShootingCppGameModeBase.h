// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingCppGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTINGGAMECPP_API AShootingCppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// �¾ �� ScoreWidget�� �����ؼ� Viewport�� ���̰��ϰ�ʹ�.
	// ������ �ְ������� �����ϰ�ʹ�.
	// �¾�� ������ 0������ �ϰ� UI�� �����ϰ� �ʹ�.
	// �Ѿ��� ���� �ı��ϸ� ������ 1�� ������Ű�� UI�� �����ϰ� �ʹ�.
public:

	int score;
	int highScore;

	void AddScore(int value);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreUIFactory;

	UPROPERTY()
	class UScoreWidget* scoreUI;

};

