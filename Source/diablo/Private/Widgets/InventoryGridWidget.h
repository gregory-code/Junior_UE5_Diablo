// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;

	void CreateLines();

private:
	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	UPROPERTY()
	class UInventoryComponent* InventoryComp;
};
