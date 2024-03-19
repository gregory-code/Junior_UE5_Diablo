// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemObject;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION()
	bool AddItem(UItemObject* itemToAdd);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FIntPoint GetTileFromIndex(int index);

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int Columns;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int Rows;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int TileSize;

	UPROPERTY()
	TArray<UItemObject*> Items;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetColumns() const;
	float GetRows() const;
	float GetTileSize() const;
	bool bIsSlotAvailable(UItemObject* itemToAdd, int addIndex);
};
