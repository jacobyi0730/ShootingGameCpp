// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverWidget::NativeConstruct()
{
	// 재시작, 종료 버튼을 눌렀을 때 나도 좀 알려줘 라고 하고싶다.
	ButtonRestart->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickRestart);

	ButtonQuit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickQuit);
}

void UGameOverWidget::OnClickRestart()
{
	// 현재 레벨의 이름을 알고싶다.
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	// 나를 뷰포트에서 제외시키고싶다.
	this->RemoveFromParent();
	// 현재 레벨을 다시 로드하고 싶다.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void UGameOverWidget::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
