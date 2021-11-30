// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	RootComponent = TheRoot;
	TheRoot->SetupAttachment(RootComponent);

	Mover = CreateDefaultSubobject<USceneComponent>(FName("Mover"));
	Mover->SetupAttachment(TheRoot);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlatformMesh"));
	PlatformMesh->SetupAttachment(Mover);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (CubeMesh.Object)
	{
		PlatformMesh->SetStaticMesh(CubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AElevator::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	PlatformMesh->SetWorldScale3D(FVector(2.0f, 2.0f, 0.2f));
}