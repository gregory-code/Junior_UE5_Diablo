// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryGridWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.h"
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

	CreateLines();
}

void UInventoryGridWidget::CreateLines()
{


}
