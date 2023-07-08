// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Public/EffectTriggers/HealthTrigger.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemComponent.h"

// Sets default values
AHealthTrigger::AHealthTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthTrigger::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AHealthTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent =  Cast<IAbilitySystemInterface>(OtherActor)->GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DecreaseHealthEffect,1,EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),AbilitySystemComponent);
		}
	}
}

