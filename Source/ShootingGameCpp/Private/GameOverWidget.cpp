// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverWidget::NativeConstruct()
{
	// �����, ���� ��ư�� ������ �� ���� �� �˷��� ��� �ϰ�ʹ�.
	ButtonRestart->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickRestart);

	ButtonQuit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickQuit);
}

void UGameOverWidget::OnClickRestart()
{
	// ���� ������ �̸��� �˰�ʹ�.
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	// ���� ����Ʈ���� ���ܽ�Ű��ʹ�.
	this->RemoveFromParent();
	// ���� ������ �ٽ� �ε��ϰ� �ʹ�.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void UGameOverWidget::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
