// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	APlayerCharacter();

private:
	UPROPERTY(visibleAnywhere, Category = "View")
	USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
	UCameraComponent* viewCamera;

	virtual void PawnClientRestart() override;

	/********************************************/
	/*                Input                     */
	/********************************************/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* inputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* moveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* lookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* jumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* inventoryInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryUI;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void Look(const FInputActionValue& InputValue);

	UFUNCTION()
	void Inventory();


	bool bInventory = false;
	FVector GetMoveFwdDir() const;
	FVector GetMoveRightDir() const;
};
