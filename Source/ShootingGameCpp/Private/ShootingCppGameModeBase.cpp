// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCppGameModeBase.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSaveGame.h"

void AShootingCppGameModeBase::BeginPlay()
{
	// �¾ �� ScoreWidget�� �����ؼ� Viewport�� ���̰��ϰ�ʹ�.
	auto ui = CreateWidget(GetWorld(), scoreUIFactory);
	scoreUI = Cast<UScoreWidget>(ui);
	scoreUI->AddToViewport();

	highScore = LoadGame(0);
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

		SaveGame();
	}
}

int AShootingCppGameModeBase::LoadGame(int defaultValue = 0)
{
	//1. ������ �����ϳ� ? (�����̸�)
	if (UGameplayStatics::DoesSaveGameExist(slotName, slotIndex))
	{
		//2. SGO = Load Slot(�����̸�, �ε�����ȣ)
		auto sgo = UGameplayStatics::LoadGameFromSlot(slotName, slotIndex);
		//3. return SGI->highScoreSave
		UShootingSaveGame* shootSGO = Cast<UShootingSaveGame>(sgo);
		if (shootSGO)
			return shootSGO->highScoreSave;
	}
	return defaultValue;
}

void AShootingCppGameModeBase::SaveGame()
{
	//1. ����Ҵ� �����̸�(HighScore)�� �ε�����ȣ(0)
	//2. SaveGameObject(SGO)�� �����Ѵ�.
	USaveGame* sgo = UGameplayStatics::CreateSaveGameObject(UShootingSaveGame::StaticClass());

	UShootingSaveGame* shootSGO = Cast<UShootingSaveGame>(sgo);

	//3. SGO->highScoreSave = highScore;
	shootSGO->highScoreSave = highScore;
	//4. Save Slot(SGO, �����̸�, �ε�����ȣ)

	UGameplayStatics::SaveGameToSlot(shootSGO, slotName, slotIndex);

}

