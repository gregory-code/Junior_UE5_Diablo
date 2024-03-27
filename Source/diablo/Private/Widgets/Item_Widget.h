// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item_Widget.generated.h"

class UItemObject;

/**
 * 
 */
UCLASS()
class UItem_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;

	void Refresh(UItemObject* MyItem, int tileSize);

private:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* BackgroundSizeBox;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY()
	UItemObject* item;

	FVector2D Size;
};
