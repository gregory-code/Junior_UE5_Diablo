// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;
	void Rescale();
private:

	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* WBP_InventoryGrid;
};
