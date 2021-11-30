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

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	Collider->SetupAttachment(TheRoot);

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
	
	DoorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("DoorAnim"));
}

void ADoor::OnAnimUpdate(float val)
{
	FRotator rot(0, val * 90, 0);

	if (IsDoorFlipped) rot.Yaw *= -1;

	TheHinge->SetRelativeRotation(rot);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (doorOpenCurve)
	{
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate"));
		DoorAnim->AddInterpFloat(doorOpenCurve, eventHandler, TEXT("Handle curve func"));
		DoorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}
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

	FVector doorSize = FVector(widthOfDoor, depthOfDoor, heightOfDoor) / 2.0f;

	doorSize.X += 50.0f;
	doorSize.Y += 25.0f;
	Collider->SetBoxExtent(FVector(widthOfDoor, depthOfDoor, heightOfDoor) / 2.0f);
	Collider->SetRelativeLocation(FVector(0.0f, 0.0f, heightOfDoor / 2.0f));
}

void ADoor::Interact()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Interacted");

	if (IsDoorOpen)
	{
		DoorAnim->Reverse();
		IsDoorOpen = false;
	}
	else
	{
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector vecToDoor = GetActorLocation() - player->GetActorLocation();
		vecToDoor.Normalize();

		float align = FVector::DotProduct(vecToDoor, GetActorRightVector());

		IsDoorFlipped = (align < 0);
		IsDoorOpen = true;
		DoorAnim->Play();
	}
}
