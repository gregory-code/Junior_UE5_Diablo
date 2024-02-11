// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DiabloPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ADiabloPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// This function calls only on the server
	virtual void OnPossess(APawn* NewPawn) override;

	// This function calls on both the listening server, and the client
	virtual void AcknowledgePossession(APawn* NewPawn) override;

private:
	void PostPossessionSetup(APawn* NewPawn);

	void SpawnGameplayUI();

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryUI;
};
