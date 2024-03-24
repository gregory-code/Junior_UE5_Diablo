// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"

FIntPoint UItemObject::GetSize() const
{
	return ItemSize;
}

void UItemObject::SetSize(int x, int y)
{
	ItemSize = FIntPoint(x, y);
}

void UItemObject::SetIcon(UMaterialInterface* newIcon)
{
	itemIcon = newIcon;
}

void UItemObject::SetIconRotated(UMaterialInterface* newIcon)
{
	itemIconRotated = newIcon;
}
