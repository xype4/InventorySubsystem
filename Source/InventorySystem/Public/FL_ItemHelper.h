// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPP_Item.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"

#include "FL_ItemHelper.generated.h"


UENUM(BlueprintType)
enum class EExecResult : uint8
{
	Valid		UMETA(DisplayName = "Valid"),
	NotValid	UMETA(DisplayName = "NotValid")
};


/**
 @FL для работы с предметами
 */
UCLASS()
class INVENTORYSYSTEM_API UFL_ItemHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Проверяет эквивалентность предметов"))
			static EItemsEqual ItemsEqual(const FItemAbstract& FirstItem, const FItemAbstract& SecondItem);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Проверяет эквивалентность двух улучшений предметов"))
			static EItemsUpgradeEqual ItemsUpgradeEqual(const FEquipmetUpgrades& FirstUpgrade, const FEquipmetUpgrades& SecondUpgrade);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Имеет ли предмет улучшения"))
			static bool ItemIsUpgraded(const FItemAbstract& Item, TArray<FEquipmetUpgrades>& ItemUpgrades);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Эквивалентны ли массивы эффектов"))
			static bool ItemEffectsIsIqual(const TArray<FEffectStatus>& FirstEffects, const TArray<FEffectStatus>& SecondEffects);

		UFUNCTION(BlueprintCallable, Category = "ItemsHelper", meta = (ToolTip = "Получить предмет из базы данных по ИД", ExpandEnumAsExecs = "OutResult"))
			static void GetItemByID(const int ID, const UDataTable* ItemsDB, EExecResult& OutResult, FItemAbstract& Item);

};
			
