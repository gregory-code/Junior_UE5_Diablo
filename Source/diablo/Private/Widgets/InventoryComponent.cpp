// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryComponent.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Items/ItemObject.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.SetNum((Columns * Rows), true);

}

FIntPoint UInventoryComponent::GetTileFromIndex(int index)
{
	FIntPoint tile;
	tile.X = index % Columns;
	tile.Y = index / Columns;

	return tile;
}

int UInventoryComponent::GetIndexFromTile(FIntPoint tile)
{
	int index = tile.X + (tile.Y * Columns);
	return index;
}

void UInventoryComponent::FinalizeItem(UItemObject* addingItem, int addIndex)
{
	FIntPoint tile = GetTileFromIndex(addIndex);

	int dimensionsX = tile.X + (addingItem->GetSize().X - 1);
	int dimensionsY = tile.Y + (addingItem->GetSize().Y - 1);

	for (int i = tile.X; i < dimensionsX; i++)
	{
		for (int j = tile.Y; j < dimensionsY; j++)
		{
			FIntPoint newTile = FIntPoint(i, j);
			Items[GetIndexFromTile(newTile)] = addingItem;
		}
	}
}

UItemObject* UInventoryComponent::GetItemAtIndex(int index)
{
	if (Items[index] == nullptr)
	{
		return nullptr;
	}

	return Items[index];
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UGameViewportClient* ViewportClient = GEngine->GameViewport;

	if (ViewportClient)
	{
		FVector2D ViewportSize;
		ViewportClient->GetViewportSize(ViewportSize);

		UE_LOG(LogTemp, Log, TEXT("Screen Resolution: %dx%d"), (int32)ViewportSize.X, (int32)ViewportSize.Y);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Viewport client is invalid!"));
	}
}

float UInventoryComponent::GetColumns() const
{
	return Columns;
}

float UInventoryComponent::GetRows() const
{
	return Rows;
}

float UInventoryComponent::GetTileSize() const
{
	return TileSize;
}

TArray<UItemObject*> UInventoryComponent::GetItems()
{
	TArray<UItemObject*> activeItems;
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i])
		{
			Items[i]->currentTile = GetTileFromIndex(i);

			if (activeItems.Contains(Items[i]) == false)
			{
				activeItems.Add(Items[i]);
			}
		}
	}
	return activeItems;
}

bool UInventoryComponent::bIsSlotAvailable(UItemObject* itemToAdd, int addIndex) // starts as the top left
{
	FIntPoint tile = GetTileFromIndex(addIndex);
	
	int dimensionsX = tile.X + (itemToAdd->GetSize().X - 1);
	int dimensionsY = tile.Y + (itemToAdd->GetSize().Y - 1);

	for (int i = tile.X; i < dimensionsX; i++)
	{
		for (int j = tile.Y; j < dimensionsY; j++)
		{
			FIntPoint check = FIntPoint(i, j);
			if (check.X >= 0 && check.Y >= 0 && check.X < Columns && check.Y < Rows)
			{
				int index = GetIndexFromTile(check);
				UItemObject* checkItem = GetItemAtIndex(index);
				if (checkItem == nullptr)
				{
					return false;
				}
				else
				{
					//Look to see if the item is occupied or not, or if it's an empty slot
					//Call a function from checkItem
				}
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

void UInventoryComponent::RemoveItem(UItemObject* itemToRemove)
{

}

bool UInventoryComponent::AddItem(UItemObject* itemToAdd)
{
	if (itemToAdd == nullptr)
	{
		return false;
	}

	for (int i = 0; i < Items.Num(); i++)
	{
		if (bIsSlotAvailable(itemToAdd, i))
		{
			FinalizeItem(itemToAdd, i);
			return true;
		}
	}

	return false;
}

