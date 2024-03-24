// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemObject.h"
#include "Item.generated.h"



UCLASS()
class AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Item Detail")
	class UBoxComponent* PickupBox;

	UPROPERTY(VisibleAnywhere, Category = "Item Detail")
	class UStaticMeshComponent* PickupMesh;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Item Detail")
	TSubclassOf<UItemObject> itemClass;

	UPROPERTY(VisibleAnywhere, Category = "Item Detail")
	UItemObject* myItem;

	UPROPERTY(EditDefaultsOnly, Category = "Item Details")
	int sizeX;

	UPROPERTY(EditDefaultsOnly, Category = "Item Details")
	int sizeY;

	UPROPERTY(EditDefaultsOnly, Category = "Item Details")
	UMaterialInterface* icon;

	UPROPERTY(EditDefaultsOnly, Category = "Item Details")
	UMaterialInterface* iconRotated;

	UFUNCTION()
	virtual void CreateDefaultItemObject();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void OnOverlapBegin(AActor* overlappedActor, AActor* otherActor);
};
