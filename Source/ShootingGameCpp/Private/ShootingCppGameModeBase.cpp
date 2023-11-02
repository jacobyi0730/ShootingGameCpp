// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCppGameModeBase.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void AShootingCppGameModeBase::BeginPlay()
{
	// �¾ �� ScoreWidget�� �����ؼ� Viewport�� ���̰��ϰ�ʹ�.
	auto ui = CreateWidget(GetWorld(), scoreUIFactory);
	scoreUI = Cast<UScoreWidget>(ui);
	scoreUI->AddToViewport();

	highScore = 0;
	scoreUI->HighScore->SetText(FText::AsNumber(highScore));

	// �¾�� ������ 0������ �ϰ� UI�� �����ϰ� �ʹ�.
	score = 0;
	scoreUI->Score->SetText(FText::AsNumber(score));

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	// �Ͻ����� �ϰ�ʹ�.
	PlayerController->SetPause(false);
	// ���콺 Ŀ�� ���̰� �ϰ�ʹ�.
	PlayerController->SetShowMouseCursor(false);
	// �Է¸�带 UI�� �ϰ�ʹ�.
	PlayerController->SetInputMode(FInputModeGameOnly());

}

// ������ ������Ű�� UI�� �����ϰ� �ʹ�.
void AShootingCppGameModeBase::AddScore(int value)
{
	score += value;
	scoreUI->Score->SetText(FText::AsNumber(score));
	// ���� ������ �ְ��������� ũ�ٸ�
	if (score > highScore)
	{
		// �ְ����� = ���� �� ���� ���ְ� �ʹ�.
		highScore = score;
		scoreUI->HighScore->SetText(FText::AsNumber(highScore));
	}
}

