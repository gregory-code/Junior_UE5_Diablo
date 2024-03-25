// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "InventoryGridWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UInventoryWidget::Rescale()
{
	WBP_InventoryGrid->Rescale();
}
