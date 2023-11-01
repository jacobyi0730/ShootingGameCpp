// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class UBoxComponent* box;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	float speed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	FVector direction;

	UPROPERTY(EditAnywhere)
	class USoundBase* explosionSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionVFX;
};
