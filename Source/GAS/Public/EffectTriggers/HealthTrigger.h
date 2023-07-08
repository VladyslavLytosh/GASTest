// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthTrigger.generated.h"



UCLASS()
class GAS_API AHealthTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,Category = Effects)
	TSubclassOf<class UGameplayEffect> DecreaseHealthEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> BoxCollision;


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
								   AActor* OtherActor, 
								   UPrimitiveComponent* OtherComp, 
								   int32 OtherBodyIndex, 
								   bool bFromSweep, 
								   const FHitResult &SweepResult );};
