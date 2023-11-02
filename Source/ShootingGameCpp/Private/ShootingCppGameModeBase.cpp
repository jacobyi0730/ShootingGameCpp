// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCppGameModeBase.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void AShootingCppGameModeBase::BeginPlay()
{
	// 태어날 때 ScoreWidget을 생성해서 Viewport에 보이게하고싶다.
	auto ui = CreateWidget(GetWorld(), scoreUIFactory);
	scoreUI = Cast<UScoreWidget>(ui);
	scoreUI->AddToViewport();

	highScore = 0;
	scoreUI->HighScore->SetText(FText::AsNumber(highScore));

	// 태어날때 점수를 0점으로 하고 UI도 갱신하고 싶다.
	score = 0;
	scoreUI->Score->SetText(FText::AsNumber(score));

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	// 일시정지 하고싶다.
	PlayerController->SetPause(false);
	// 마우스 커서 보이게 하고싶다.
	PlayerController->SetShowMouseCursor(false);
	// 입력모드를 UI만 하고싶다.
	PlayerController->SetInputMode(FInputModeGameOnly());

}

// 점수를 증가시키고 UI도 갱신하고 싶다.
void AShootingCppGameModeBase::AddScore(int value)
{
	score += value;
	scoreUI->Score->SetText(FText::AsNumber(score));
	// 만약 점수가 최고점수보다 크다면
	if (score > highScore)
	{
		// 최고점수 = 점수 로 갱신 해주고 싶다.
		highScore = score;
		scoreUI->HighScore->SetText(FText::AsNumber(highScore));
	}
}

