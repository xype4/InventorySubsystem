// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_Item.h"

#include "DA_Item.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class INVENTORYSYSTEM_API UDA_Item : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Config")
		TArray<FItemAbstract> Items;

	TArray<FItemAbstract>* GetItemsP();

	UFUNCTION(BlueprintCallable, Category = "ItemsDataAsset")
		void AddNewItem();

	UFUNCTION(BlueprintCallable, Category = "ItemsDataAsset")
		bool RemoveItem(int id);

	UFUNCTION(BlueprintCallable, Category = "ItemsDataAsset")
		bool GetItem(int id, FItemAbstract& Item);

	UFUNCTION(BlueprintCallable, Category = "ItemsDataAsset")
		bool ReplaceItemByID(FItemAbstract NewItem);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsDataAsset")
		void GetItems(TArray<FItemAbstract>& ItemsRef);
};
