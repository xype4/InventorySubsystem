// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPP_Item.h"
#include "Engine/AssetManager.h"
#include "Internationalization/Text.h"
#include "DA_Item.h"

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
			static bool ItemEffectsIsIqual(const TArray<FEffectAbstract>& FirstEffects, const TArray<FEffectAbstract>& SecondEffects);

		UFUNCTION(BlueprintCallable, Category = "ItemsHelper", meta = (ToolTip = "Получить предмет из базы данных по ИД", ExpandEnumAsExecs = "OutResult"))
			static void GetItemByID(const int ID, const UDA_Item* ItemsDA, EExecResult& OutResult, FItemAbstract& Item);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Получить текст категории предмета"))
			static FText GetItemCategoryName(const EItemCategory& Category);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Получить текст типа предмета"))
			static FText GetItemTypeName(const EItemType& Category);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Получить текст подтипа предмета"))
			static FText GetItemSubTypeName(const EItemSubType& Category);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ItemsHelper", meta = (ToolTip = "Получить список категирий предметов"))
			static TArray<EItemCategory> GetItemCategories();

		template <typename T>
		static TArray<T> GetEnumList();

		static FText ItemCategoryArmor;
		static FText ItemCategoryBook;
		static FText ItemCategoryOther;
		static FText ItemCategoryPotion;
		static FText ItemCategoryWeapon;
		static FText ItemCategoryAccessory;

		static FText ItemCategoryAxe;
		static FText ItemCategoryBody;
		static FText ItemCategoryBoots;
		static FText ItemCategoryBow;
		static FText ItemCategoryGloves;
		static FText ItemCategoryHelment;
		static FText ItemCategoryLeg;
		static FText ItemCategoryMace;
		static FText ItemCategorySword;
		static FText ItemCategoryShield;
		static FText ItemCategoryRing;
		static FText ItemCategoryNeck;

		static FText ItemCategoryHeavy;
		static FText ItemCategoryLight;
		static FText ItemCategoryMedium;

		static FText ItemCategoryNone;
};

