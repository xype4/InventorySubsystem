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
 * @�������� ���������
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
 * @���� ���������
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
 * @�������
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
 * @���� ��������, ���������� � ���������
 */


UENUM(BlueprintType)
enum class EEffectStatusType : uint8
{
	// �������� ����
	PhysicalDamage		UMETA(DisplayName = "PhysicalDamage"), // ���������� ���� (�������, ��������, �������)
	MagicalDamage		UMETA(DisplayName = "MagicalDamage"),  // ���������� ���� (������������� ���������� ���)
	TrueDamage			UMETA(DisplayName = "TrueDamage"), // ���������� ����� � �������������

	// ��������� ����
	FireDamage			UMETA(DisplayName = "FireDamage"),     // �������� ����
	IceDamage			UMETA(DisplayName = "IceDamage"),      // ������� ����
	LightningDamage		UMETA(DisplayName = "LightningDamage"), // ������������� ����
	PoisonDamage		UMETA(DisplayName = "PoisonDamage"),   // �������� ����
	BleedingDamage		UMETA(DisplayName = "BleedingDamage"),  // ������������ 
	RadiantDamage		UMETA(DisplayName = "RadiantDamage"),  // ������� ����
	NecroticDamage      UMETA(DisplayName = "NecroticDamage"), // ������������� ����

	// ���� �� ���������������
	StaminaDamage		UMETA(DisplayName = "StaminaDamage"),  // ���� �� �������
	ManaDamage			UMETA(DisplayName = "ManaDamage"),     // ���� �� ����
	ForceDamage			UMETA(DisplayName = "ForceDamage"),     // ���� ���. ����
	MagicDamage			UMETA(DisplayName = "MagicDamage"),     // ���� ���. ����

	// ������������� �������
	ManaRecovery		UMETA(DisplayName = "ManaRecovery"),  // �������������� ����
	StaminaRecovery		UMETA(DisplayName = "StaminaRecovery"),  // �������������� �������
	HealthRecovery		UMETA(DisplayName = "HealthRecovery"),  // �������������� ��

	ManaIncrease		UMETA(DisplayName = "ManaIncrease"),  // ��������� ����
	StaminaIncrease		UMETA(DisplayName = "StaminaIncrease"),  // ��������� �������
	HealthIncrease		UMETA(DisplayName = "HealthIncrease"),  // ��������� ��

};

/**
 * @���������, ����������� �������� �������
 */

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEffectStatus
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "��� �������"))
			EEffectStatusType EffectType;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "����������� ������� ������"))
			float EffectProbability;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "����������� ������� � �������"))
			float EffectPerSecond;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "����� �������"))
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
 * @���������, ����������� ��������� ���������� (����������� � ��)
 */


USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEquipmetUpgrades
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "�������� ���������"))
		FText UpgradeName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "�������� ���������", MultiLine = "true"))
		FText UpgradeDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "��������� ������� (��� ����������)"))
		TArray<FEffectStatus> UpgradePassiveEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "�������� ������� �� ���� (��� �������������, �����)"))
		TArray<FEffectStatus> UpgradeActiveTargetEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "�������� ������� �� ���� (��� �������������, �����)"))
		TArray<FEffectStatus> UpgradeActiveSelfEffects;
};


/**
 * @���������, ����������� ����������� ������� ������� ��� ����������
 */

USTRUCT (BlueprintType)
struct INVENTORYSYSTEM_API FItemAbstract: public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ClampMin = 0, UIMin = 0, ToolTip = "ID ��������"))
			int ItemID;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "�������� ��������"))
			FText ItemName;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "�������� ��������", MultiLine = "true"))
			FText ItemDescription;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "����� ��������"))
			float ItemMass;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "��������� ��������"))
			float ItemPrice;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "����������� ��������"))
			bool bCanDrop;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "����������� ������������"))
			bool bCanUse;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "��� ��������"))
			EItemCategory ItemCategory;
	
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "��������� ��������"))
			EItemType ItemType;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Category", meta = (ToolTip = "������������ ��������"))
			EItemSubType ItemSubType;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "��������� ������� (��� ����������)"))
			TArray<FEffectStatus> ItemPassiveEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "�������� ������� �� ���� (��� �������������, �����)"))
			TArray<FEffectStatus> ItemActiveTargetEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "�������� ������� �� ���� (��� �������������, �����)"))
			TArray<FEffectStatus> ItemActiveSelfEffects;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects", meta = (ToolTip = "��������� �� ��������"))
			TArray<FEquipmetUpgrades> ItemUpgrades;


		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "��� ��������"))
			TSoftObjectPtr<UStaticMesh> Mesh;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh", meta = (ToolTip = "�������� ��������"))
			TSoftObjectPtr<UMaterial> UMaterialInterface;

};


/**
 * @���������, ����������� ���������� ������� ������� � ����������� � �����
 */

USTRUCT (BlueprintType)
struct INVENTORYSYSTEM_API FItemInstance
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ToolTip = "�������"))
			FItemAbstract ItemAbstract;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Main", meta = (ClampMin = 0, UIMin = 0, ToolTip = "���������� ���������"))
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



