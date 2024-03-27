// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryGridWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.h"
#include "Engine/Canvas.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widgets/Item_Widget.h"
#include "Containers/Map.h"
#include "Items/ItemObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player)
	{
		InventoryComp = player->GetComponentByClass<UInventoryComponent>();
	}

	if (InventoryComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Got inventory"), *GetName());
	}

	UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	if (GridBorderSlot)
	{
		GridBorderSlot->SetSize(FVector2D(InventoryComp->GetColumns() * InventoryComp->GetTileSize(), InventoryComp->GetRows() * InventoryComp->GetTileSize()));
	}
}

void UInventoryGridWidget::CreateLine(FSlateWindowElementList& OutDrawElements, int32 LayerId, FPaintGeometry geo, FVector2D Start, FVector2D End) const
{
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, geo, TArray<FVector2D>{Start, End}, ESlateDrawEffect::None, FLinearColor::White);
	//StartLines.Add(Start);
	//EndLines.Add(End);
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (InventoryComp == nullptr)
		return 0;

	int rows = InventoryComp->GetRows();
	int columns = InventoryComp->GetColumns();
	int tileSize = InventoryComp->GetTileSize();

	tileSize *= UWidgetLayoutLibrary::GetViewportScale(this);

	FPaintGeometry geo;
	geo.DrawPosition = AllottedGeometry.AbsolutePosition;
	geo.GetLocalSize() = AllottedGeometry.GetLocalSize();

	for (int i = 0; i <= columns; i++)
	{
		float XLocal = i * tileSize;
		FVector2D Start = FVector2D(XLocal, 0);
		FVector2D End = FVector2D(XLocal, (rows * tileSize));
		CreateLine(OutDrawElements, LayerId, geo, Start, End);
	}

	for (int i = 0; i <= rows; i++)
	{
		float YLocal = i * tileSize;
		FVector2D Start = FVector2D(0, YLocal);
		FVector2D End = FVector2D((columns * tileSize), YLocal);
		CreateLine(OutDrawElements, LayerId, geo, Start, End);
	}

	return 0;
}

void UInventoryGridWidget::RefreshBoard()
{
	for (UItem_Widget* itemWid : Item_Widgets)
	{
		itemWid->RemoveFromParent();
	}
	Item_Widgets.Empty();
	GridCanvasPanel->ClearChildren();

	int tileSize = InventoryComp->GetTileSize();

	TArray<UItemObject*> items;
	for (int i = 0; i < items.Num(); i++)
	{
		Item_Widgets.Add(CreateWidget<UItem_Widget>(this, ItemWidgetClass));
		if (Item_Widgets[i])
		{
			GridCanvasPanel->AddChild(Item_Widgets[i]);
			UCanvasPanelSlot* itemPanel = Cast<UCanvasPanelSlot>(Item_Widgets[i]->Slot);
			itemPanel->SetAutoSize(true);
			FVector2D pos = FVector2D((items[i]->currentTile.X * tileSize), (items[i]->currentTile.Y * tileSize));
			itemPanel->SetPosition(pos);

			Item_Widgets[i]->Refresh(items[i], tileSize);
			// Bind this to an event where it gets removed -> Add a delegate
		}
	}
}
