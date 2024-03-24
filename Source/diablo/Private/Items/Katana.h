// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Katana.generated.h"

/**
 * 
 */
UCLASS()
class AKatana : public AItem
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void CreateDefaultItemObject() override;
};
