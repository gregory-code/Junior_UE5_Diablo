// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Widgets/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	PickupMesh->SetupAttachment(GetRootComponent());
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RootComponent = PickupMesh;

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Box"));
	PickupBox->SetBoxExtent(FVector(5, 5, 5));
	PickupBox->AttachToComponent(PickupMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::CreateDefaultItemObject()
{

}

void AItem::OnOverlapBegin(AActor* overlappedActor, AActor* otherActor)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(otherActor);
	if (!player)
	{
		return;
	}

	UInventoryComponent* inventory = player->GetComponentByClass<UInventoryComponent>();

	if (inventory)
	{
		if (inventory->AddItem(itemClass))
		{
			Destroy();
		}
	}
}

