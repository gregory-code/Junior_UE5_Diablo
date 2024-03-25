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

	void CreateLine(FSlateWindowElementList& OutDrawElements, int32 LayerId, FPaintGeometry geo, FVector2D Start, FVector2D End) const;
	void Rescale();
private:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, 
		FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UFUNCTION()
	void RefreshBoard();

	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	UPROPERTY()
	class UInventoryComponent* InventoryComp;

	UPROPERTY()
	TArray<FVector2D> StartLines;

	UPROPERTY()
	TArray<FVector2D> EndLines;
};
