// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UItemObject : public UObject
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Item Details")
	FIntPoint ItemSize;

	UPROPERTY(VisibleAnywhere, Category = "Item Details")
	UMaterialInterface* itemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Item Details")
	UMaterialInterface* itemIconRotated;

public:

	UFUNCTION()
	FIntPoint GetSize() const;

	UFUNCTION()
	void SetSize(int x, int y);

	UFUNCTION()
	void SetIcon(UMaterialInterface* newIcon);

	UFUNCTION()
	void SetIconRotated(UMaterialInterface* newIcon);

	UPROPERTY(VisibleAnywhere, Category = "Item Details")
	bool bRotated;
};
