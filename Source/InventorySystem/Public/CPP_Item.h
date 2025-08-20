// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Internationalization/Text.h"
#include "UObject/SoftObjectPtr.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Engine/DataTable.h"

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
 * @Типы эффектов, применимых к персонажу
 */


UENUM(BlueprintType)
enum class EEffectStatusType : uint8
{
	// Основные типы
	PhysicalDamage		UMETA(DisplayName = "PhysicalDamage"), // Физический урон (рубящий, дробящий, колющий)
	MagicalDamage		UMETA(DisplayName = "MagicalDamage"),  // Магический урон (универсальный магический тип)
	TrueDamage			UMETA(DisplayName = "TrueDamage"), // Игнорирует броню и сопротивления

	// Стихийный урон
	FireDamage			UMETA(DisplayName = "FireDamage"),     // Огненный урон
	IceDamage			UMETA(DisplayName = "IceDamage"),      // Ледяной урон
	LightningDamage		UMETA(DisplayName = "LightningDamage"), // Электрический урон
	PoisonDamage		UMETA(DisplayName = "PoisonDamage"),   // Ядовитый урон
	BleedingDamage		UMETA(DisplayName = "BleedingDamage"),  // Кровотечение 
	RadiantDamage		UMETA(DisplayName = "RadiantDamage"),  // Светлый урон
	NecroticDamage      UMETA(DisplayName = "NecroticDamage"), // Некротический урон

	// Урон по характеристикам
	StaminaDamage		UMETA(DisplayName = "StaminaDamage"),  // Урон по стамине
	ManaDamage			UMETA(DisplayName = "ManaDamage"),     // Урон по мане
	ForceDamage			UMETA(DisplayName = "ForceDamage"),     // Урон физ. силе
	MagicDamage			UMETA(DisplayName = "MagicDamage"),     // Урон маг. силе

	// Положительные эффекты
	ManaRecovery		UMETA(DisplayName = "ManaRecovery"),  // Восстановление маны
	StaminaRecovery		UMETA(DisplayName = "StaminaRecovery"),  // Восстановление стамины
	HealthRecovery		UMETA(DisplayName = "HealthRecovery"),  // Восстановление хп

	ManaIncrease		UMETA(DisplayName = "ManaIncrease"),  // Повышение маны
	StaminaIncrease		UMETA(DisplayName = "StaminaIncrease"),  // Повышение стамины
	HealthIncrease		UMETA(DisplayName = "HealthIncrease"),  // Повышение хп

};

/**
 * @Структура, описывающая действие эффекта
 */

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEffectStatus
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Тип эффекта"))
			EEffectStatusType EffectType;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Вероятность вызвать эффект"))
			float EffectProbability;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Воздействие эффекта в секунду"))
			float EffectPerSecond;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Время эффекта"))
			float EffectTime;

		bool operator==(const FEffectStatus& Other) const
		{
			bool isTypeEqual = EffectType == Other.EffectType;
			bool isProbabilityEqual = FMath::IsNearlyEqual(EffectProbability, Other.EffectProbability, 0.0001f);
			bool isEffectPerSecondEqual = FMath::IsNearlyEqual(EffectPerSecond, Other.EffectPerSecond, 0.0001f);
			bool isEffectTimeEqual = FMath::IsNearlyEqual(EffectTime, Other.EffectTime, 0.0001f);

			return isTypeEqual && isProbabilityEqual && isEffectPerSecondEqual && isEffectTimeEqual;
		}

		bool operator!=(const FEffectStatus& Other) const
		{
			return !(*this == Other); 
		}
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
		TArray<FEffectStatus> UpgradePassiveEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на ЦЕЛЬ (при использовании, атаке)"))
		TArray<FEffectStatus> UpgradeActiveTargetEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на СЕБЯ (при использовании, атаке)"))
		TArray<FEffectStatus> UpgradeActiveSelfEffects;
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
			TArray<FEffectStatus> ItemPassiveEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на ЦЕЛЬ (при использовании, атаке)"))
			TArray<FEffectStatus> ItemActiveTargetEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Активные эффекты на СЕБЯ (при использовании, атаке)"))
			TArray<FEffectStatus> ItemActiveSelfEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "Улучшения на предмете"))
			TArray<FEquipmetUpgrades> ItemUpgrades;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "Меш предмета"))
			TSoftObjectPtr<UStaticMesh> Mesh;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "Материал предмета"))
			TSoftObjectPtr<UMaterial> UMaterialInterface;

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



