// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));

	RootComponent = TheRoot;
	TheRoot->SetupAttachment(RootComponent);


	TheHinge = CreateDefaultSubobject<USceneComponent>(FName("TheHinge"));
	TheHinge->SetupAttachment(TheRoot);

	TheMeshDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshDoor"));
	TheMeshDoor->SetupAttachment(TheHinge);

	TheMeshFrame = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TheMeshFrame"));
	TheMeshFrame->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		TheMeshDoor->SetStaticMesh(TheCubeMesh.Object);
		TheMeshFrame->SetStaticMesh(TheCubeMesh.Object);
	}
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheMeshDoor->SetWorldScale3D(FVector(widthOfDoor, depthOfDoor, heightOfDoor) / 100);

	TheMeshDoor->SetRelativeLocation(FVector(widthOfDoor / 2, 0, heightOfDoor / 2));

	TheHinge->SetRelativeLocation(FVector(-widthOfDoor / 2, 0, 0));

	TheMeshFrame->AddInstance(FTransform(
		FRotator(0, 0, 0), 
		FVector(widthOfDoor / 2 + depthOfDoor / 2, 0, heightOfDoor / 2), 
		FVector(depthOfDoor, depthOfDoor, heightOfDoor) / 100));
}

void ADoor::Interact()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Interacted");
}
