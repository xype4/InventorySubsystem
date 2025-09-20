// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Internationalization/Text.h"
#include "UObject/SoftObjectPtr.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Engine/DataTable.h"
#include "CPP_StatsComponent.h"

#include "CPP_Item.generated.h"

/**
 * @Категрии предметов
 */

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Weapon     UMETA(DisplayName = "Weapon"),
	Armor      UMETA(DisplayName = "Armor"),
	Accessory  UMETA(DisplayName = "Accessory"),
	Potion     UMETA(DisplayName = "Potion"),
	Book       UMETA(DisplayName = "Book"),
	Other      UMETA(DisplayName = "Other")
};

UENUM(BlueprintType)
enum class EItemsEqual : uint8
{
	FullEqual				UMETA(DisplayName = "FullEqual"),
	NotEqualUpgrades		UMETA(DisplayName = "NotEqualUpgrades"),
	NotEqual				UMETA(DisplayName = "NotEqual")
};

UENUM(BlueprintType)
enum class EItemsUpgradeEqual : uint8
{
	FullEqual		UMETA(DisplayName = "FullEqual"),
	NotEqualName    UMETA(DisplayName = "NotEqualNameOrDescription"),
	NotEqualEffect	UMETA(DisplayName = "NotEqualEffect"),
	NotEqual		UMETA(DisplayName = "NotEqual")
};

/**
 * @Типы предметов
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Sword		UMETA(DisplayName = "Sword"),
	Axe			UMETA(DisplayName = "Axe"), 
	Mace		UMETA(DisplayName = "Mace"), 
	Bow			UMETA(DisplayName = "Bow"),   
	Helment		UMETA(DisplayName = "Helmet"),   
	Body		UMETA(DisplayName = "Body"),
	Gloves		UMETA(DisplayName = "Gloves"),
	Leg			UMETA(DisplayName = "Leg Armor"), 
	Boots		UMETA(DisplayName = "Boots"),    
	Neck		UMETA(DisplayName = "Neck"),
	Ring		UMETA(DisplayName = "Ring"),
	Nothing		UMETA(DisplayName = "Nothing"),
	Shield		UMETA(DisplayName = "Shield")
};

/**
 * @Подтипы
 */

UENUM(BlueprintType)
enum class EItemSubType : uint8
{
	Heavy		UMETA(DisplayName = "Heavy"),
	Light		UMETA(DisplayName = "Light"),
	Nothing		UMETA(DisplayName = "Nothing"),
	Medium		UMETA(DisplayName = "Medium")
};

/**
 * @Структура, описывающая улучшения экипировки (зачарования и ид)
 */


USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEquipmetUpgrades
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Название улучшения"))
		FText UpgradeName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Описание улучшения", MultiLine = "true"))
		FText UpgradeDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Пассивные эффекты (при экипировке)"))
		TArray<FEffectAbstract> UpgradePassiveEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на ЦЕЛЬ (при использовании, атаке)"))
		TArray<FEffectAbstract> UpgradeActiveTargetEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на СЕБЯ (при использовании, атаке)"))
		TArray<FEffectAbstract> UpgradeActiveSelfEffects;
};


/**
 * @Структура, описывающая абстрактный предмет предмет БЕЗ КОЛИЧЕСТВА
 */

USTRUCT (BlueprintType)
struct INVENTORYSYSTEM_API FItemAbstract: public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ClampMin = 0, UIMin = 0, ToolTip = "ID предмета"))
			int ItemID;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Название предмета"))
			FText ItemName;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Описание предмета", MultiLine = "true"))
			FText ItemDescription;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Масса предмета"))
			float ItemMass;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Стоимость предмета"))
			float ItemPrice;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Возможность выкинуть"))
			bool bCanDrop;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Возможность использовать"))
			bool bCanUse;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "Тип предмета"))
			EItemCategory ItemCategory;
	
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "Категория предмета"))
			EItemType ItemType;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "Подкатегория предмета"))
			EItemSubType ItemSubType;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Пассивные эффекты (при экипировке)"))
			TArray<FEffectAbstract> ItemPassiveEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на ЦЕЛЬ (при использовании, атаке)"))
			TArray<FEffectAbstract> ItemActiveTargetEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на СЕБЯ (при использовании, атаке)"))
			TArray<FEffectAbstract> ItemActiveSelfEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Улучшения на предмете"))
			TArray<FEquipmetUpgrades> ItemUpgrades;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "Меш предмета"))
			TSoftObjectPtr<UStaticMesh> Mesh;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "Материал предмета"))
			TSoftObjectPtr<UMaterialInstance> Material;

};


/**
 * @Структура, описывающая конкретынй предмет предмет С КОЛИЧЕСТВОМ в слоте
 */

USTRUCT (BlueprintType)
struct INVENTORYSYSTEM_API FItemInstance
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "Предмет"))
			FItemAbstract ItemAbstract;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ClampMin = 0, UIMin = 0, ToolTip = "Количество предметов"))
			int Count;

		FItemInstance(FItemAbstract ItemAbstractConstructor, int CountConstructor)
		{
			ItemAbstract = ItemAbstractConstructor;
			Count = CountConstructor;
		}

		FItemInstance(FItemAbstract ItemAbstractConstructor)
		{
			ItemAbstract = ItemAbstractConstructor;
			Count = 1;
		}

		FItemInstance()
		{
			ItemAbstract = FItemAbstract();
			Count = 0;
		}
};



