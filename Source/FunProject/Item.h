// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FunProjectCharacter.h"
#include "Item.generated.h"

UCLASS()
class FUNPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UShapeComponent* TBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_TBox;

	AFunProjectCharacter* MyPlayerController;

	UPROPERTY(EditAnywhere)
		FString ItemName = FString(TEXT(""));

	void Pickup();
	void GetPlayer(AActor* Player);

	bool ItemIsWithinRange = false;

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* dummy, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* dummy, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
