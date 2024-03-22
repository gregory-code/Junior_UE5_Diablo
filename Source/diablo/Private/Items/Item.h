// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemObject;

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

	UFUNCTION()
	virtual void CreateDefaultItemObject();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void OnOverlapBegin(AActor* overlappedActor, AActor* otherActor);
};
