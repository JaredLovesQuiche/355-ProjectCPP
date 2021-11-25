// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableThing.h"
#include "UObject/ConstructorHelpers.h"
#include "Door.generated.h"

UCLASS()
class FUNPROJECT_API ADoor : public AActor, public IInteractableThing
{
	GENERATED_BODY()
	
public:	
	ADoor();

	// scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	// scene component for hinge
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheHinge;

	// mesh for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheMeshDoor;
	
	// mesh for door frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TheMeshFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door Settings")
	float widthOfDoor = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door Settings")
	float heightOfDoor = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door Settings")
	float depthOfDoor = 25;
	// collider ?

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();
};
