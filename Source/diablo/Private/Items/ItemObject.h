// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS()
class UItemObject : public UObject
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Item Details")
	FIntPoint ItemSize;

public:

	UFUNCTION()
	FIntPoint GetSize() const;

};
