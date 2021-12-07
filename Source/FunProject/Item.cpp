// Fill out your copyright notice in the Description page of Project Settings.

#include "FunProject.h"
#include "Item.h"
#include "Engine.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TBox->SetGenerateOverlapEvents(true);
	TBox->OnComponentBeginOverlap.AddDynamic(this, &AItem::TriggerEnter);
	TBox->OnComponentEndOverlap.AddDynamic(this, &AItem::TriggerExit);

	RootComponent = TBox;

	SM_TBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	SM_TBox->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyPlayerController != NULL) // null check
	{
		if (MyPlayerController->IsPickingUp && ItemIsWithinRange)
		{
			Pickup();
		}
	}
}

void AItem::GetPlayer(AActor* Player)
{
	MyPlayerController = Cast<AFunProjectCharacter>(Player);
}

void AItem::Pickup()
{
	MyPlayerController->Inventory.Add(*ItemName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You picked the item up!"));
	Destroy();
}

void AItem::TriggerEnter(UPrimitiveComponent* dummy, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	ItemIsWithinRange = true;
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, FString::Printf(TEXT("Press E to pickup %s"), *ItemName));
	GetPlayer(OtherActor);
}

void AItem::TriggerExit(UPrimitiveComponent* dummy, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemIsWithinRange = false;
}