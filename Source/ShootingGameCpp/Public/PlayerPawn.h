// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "PlayerPawn.generated.h"

//class UBoxComponent; // ���漱�� forward declaration

UCLASS()
class SHOOTINGGAMECPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* cube;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* box; // ������ ���� ����� class�� �̴̹� ���漱���̴�. 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 500.f;

	float h, v;
	void AxisHorizontal(float value);
	void AxisVertical(float value);
};
