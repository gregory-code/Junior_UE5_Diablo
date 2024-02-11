// Fill out your copyright notice in the Description page of Project Settings.


#include "DiabloPlayerController.h"
#include "PlayerCharacter.h"
#include "Widgets/InventoryWidget.h"

void ADiabloPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("On Possess Called on Server"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("On Possess Called Client"));
	}

	PostPossessionSetup(NewPawn);
}

void ADiabloPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ack Called on Server"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ack Called Client"));
	}

	PostPossessionSetup(NewPawn);
}

void ADiabloPlayerController::PostPossessionSetup(APawn* NewPawn)
{
	PlayerCharacter = Cast<APlayerCharacter>(NewPawn);
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Needs PlayerCharacter as Pawn"));
		return;
	}

	//SpawnGameplayUI();
}

void ADiabloPlayerController::SpawnGameplayUI()
{
	if (!PlayerCharacter)
	{

		return;
	}

	if (!InventoryUI)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, missing gameplayUI class"), *GetName());
		return;
	}

	//returns true if it's a player on the local side of you playing
	if (!IsLocalPlayerController())
	{

		return;
	}

	InventoryUI = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);

	if (InventoryUI)
	{

		InventoryUI->AddToViewport();
	}
}
