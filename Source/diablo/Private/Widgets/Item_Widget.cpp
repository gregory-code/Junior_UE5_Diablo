// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Item_Widget.h"
#include "Items/ItemObject.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"

void UItem_Widget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UItem_Widget::Refresh(UItemObject* MyItem, int tileSize)
{
	item = MyItem;

	FIntPoint dimensions = MyItem->GetSize();
	Size.X = dimensions.X * tileSize;
	Size.Y = dimensions.Y * tileSize;

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	UCanvasPanelSlot* ImageSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
	ImageSlot->SetSize(Size);

	FSlateBrush brush;
	if (MyItem->bRotated)
	{
		brush.SetResourceObject(MyItem->GetRotatedIcon());
	}
	else
	{
		brush.SetResourceObject(MyItem->GetIcon());
	}
	brush.SetImageSize(Size);

	ItemImage->SetBrush(brush);
}
