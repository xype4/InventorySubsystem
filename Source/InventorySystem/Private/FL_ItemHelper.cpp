// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_ItemHelper.h"
#include "Math/UnrealMathUtility.h"
#include "..\Public\FL_ItemHelper.h"

FText UFL_ItemHelper::ItemCategoryArmor = NSLOCTEXT("Items", "ItemCategoryArmor", "Armor");
FText UFL_ItemHelper::ItemCategoryBook = NSLOCTEXT("Items", "ItemCategoryBook", "Book");
FText UFL_ItemHelper::ItemCategoryOther = NSLOCTEXT("Items", "ItemCategoryOther", "Other");
FText UFL_ItemHelper::ItemCategoryPotion = NSLOCTEXT("Items", "ItemCategoryPotion", "Potion");
FText UFL_ItemHelper::ItemCategoryWeapon = NSLOCTEXT("Items", "ItemCategoryWeapon", "Wepon");
FText UFL_ItemHelper::ItemCategoryAccessory = NSLOCTEXT("Items", "ItemCategoryAccessory", "Accessory");

FText UFL_ItemHelper::ItemCategoryAxe = NSLOCTEXT("Items", "ItemCategoryAxe", "Axe");
FText UFL_ItemHelper::ItemCategoryBody = NSLOCTEXT("Items", "ItemCategoryBody", "Body");
FText UFL_ItemHelper::ItemCategoryBoots = NSLOCTEXT("Items", "ItemCategoryBoots", "Boots");
FText UFL_ItemHelper::ItemCategoryBow = NSLOCTEXT("Items", "ItemCategoryBow", "Bow");
FText UFL_ItemHelper::ItemCategoryGloves = NSLOCTEXT("Items", "ItemCategoryGloves", "Gloves");
FText UFL_ItemHelper::ItemCategoryHelment = NSLOCTEXT("Items", "ItemCategoryHelment", "Helment");
FText UFL_ItemHelper::ItemCategoryLeg = NSLOCTEXT("Items", "ItemCategoryLeg", "Leg");
FText UFL_ItemHelper::ItemCategoryMace = NSLOCTEXT("Items", "ItemCategoryMace", "Mace");
FText UFL_ItemHelper::ItemCategorySword = NSLOCTEXT("Items", "ItemCategorySword", "Sword");
FText UFL_ItemHelper::ItemCategoryShield = NSLOCTEXT("Items", "ItemCategoryShield", "Shield");
FText UFL_ItemHelper::ItemCategoryRing = NSLOCTEXT("Items", "ItemCategoryRing", "Ring");
FText UFL_ItemHelper::ItemCategoryNeck = NSLOCTEXT("Items", "ItemCategoryNeck", "Neck");

FText UFL_ItemHelper::ItemCategoryHeavy = NSLOCTEXT("Items", "ItemCategoryHeavy", "Heavy");
FText UFL_ItemHelper::ItemCategoryLight = NSLOCTEXT("Items", "ItemCategoryLight", "Light");
FText UFL_ItemHelper::ItemCategoryMedium = NSLOCTEXT("Items", "ItemCategoryMedium", "Medium");


FText UFL_ItemHelper::ItemCategoryNone = NSLOCTEXT("Items", "ItemCategoryNone", "None");


EItemsEqual UFL_ItemHelper::ItemsEqual(const FItemAbstract& FirstItem, const FItemAbstract& SecondItem)
{
	if(FirstItem.ItemID == SecondItem.ItemID)
	{
		TArray<FEquipmetUpgrades> FistItemUpgrades = FirstItem.ItemUpgrades;
		TArray<FEquipmetUpgrades> SecondItemUpgrades = SecondItem.ItemUpgrades;

		if (FistItemUpgrades.Num() == SecondItemUpgrades.Num())
		{
			for (int i = 0; i < FistItemUpgrades.Num(); i++) {
				if (ItemsUpgradeEqual(FistItemUpgrades[i], SecondItemUpgrades[i]) == EItemsUpgradeEqual::FullEqual)
				{
					continue;
				}

				else
				{
					return EItemsEqual::NotEqualUpgrades;
				}
			}
		}
		else 
		{
			return EItemsEqual::NotEqualUpgrades;
		}

		return EItemsEqual::FullEqual;
	}

	return EItemsEqual::NotEqual;
};

EItemsUpgradeEqual UFL_ItemHelper::ItemsUpgradeEqual(const FEquipmetUpgrades& FirstUpgrade, const FEquipmetUpgrades& SecondUpgrade)
{
	bool isEqualNames = FirstUpgrade.UpgradeName.EqualTo(SecondUpgrade.UpgradeName);
	bool isEqualDescriptions = FirstUpgrade.UpgradeDescription.EqualTo(SecondUpgrade.UpgradeDescription);

	bool isNameEqual = isEqualNames && isEqualDescriptions;

	bool isPassiveEffectsEqual = ItemEffectsIsIqual(FirstUpgrade.UpgradePassiveEffects, SecondUpgrade.UpgradePassiveEffects);
	bool isActiveTargetEffectsEqual = ItemEffectsIsIqual(FirstUpgrade.UpgradeActiveTargetEffects, SecondUpgrade.UpgradeActiveTargetEffects);
	bool isActiveSelfEffectsEqual = ItemEffectsIsIqual(FirstUpgrade.UpgradeActiveSelfEffects, SecondUpgrade.UpgradeActiveSelfEffects);

	bool isEffectsEqual = isPassiveEffectsEqual && isActiveTargetEffectsEqual && isActiveSelfEffectsEqual;

	if(isNameEqual == false && isEffectsEqual == false)
		return EItemsUpgradeEqual::NotEqual;

	if (isNameEqual == false)
		return EItemsUpgradeEqual::NotEqualName;

	if (isEffectsEqual == false)
		return EItemsUpgradeEqual::NotEqualEffect;

	return EItemsUpgradeEqual::FullEqual;
}

bool UFL_ItemHelper::ItemIsUpgraded(const FItemAbstract& Item, TArray<FEquipmetUpgrades>& ItemUpgrades)
{
	return ItemUpgrades.Num() >= 1;
}

bool UFL_ItemHelper::ItemEffectsIsIqual(const TArray<FEffectAbstract>& FirstEffects, const TArray<FEffectAbstract>& SecondEffects)
{
	if (FirstEffects.Num() == SecondEffects.Num())
	{
		for (int i = 0; i < FirstEffects.Num(); i++) {
			if (FirstEffects[i].operator==(SecondEffects[i]))
			{
				continue;
			}

			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

void UFL_ItemHelper::GetItemByID(const int ID, const UDA_Item* ItemsDA, EExecResult& OutResult, FItemAbstract& Item)
{
	if (ItemsDA)
	{
		for(auto const currentItem: ItemsDA->Items)
		{
			if(currentItem.ItemID == ID)
			{
				OutResult = EExecResult::Valid;
				Item = currentItem;
				return;
			}
		}
	}
	OutResult = EExecResult::NotValid;
	Item = FItemAbstract();
}

FText UFL_ItemHelper::GetItemCategoryName(const EItemCategory& Category)
{
	switch (Category)
	{
	case EItemCategory::Armor:
		return ItemCategoryArmor;

	case EItemCategory::Book:
		return ItemCategoryBook;

	case EItemCategory::Other:
		return ItemCategoryOther;

	case EItemCategory::Potion:
		return ItemCategoryPotion;

	case EItemCategory::Weapon:
		return ItemCategoryWeapon;

	case EItemCategory::Accessory:
		return ItemCategoryAccessory;

	default:
		return ItemCategoryNone;
	}
}

FText UFL_ItemHelper::GetItemTypeName(const EItemType& Category)
{
	switch (Category)
	{
	case EItemType::Axe:
		return ItemCategoryAxe;

	case EItemType::Body:
		return ItemCategoryBody;

	case EItemType::Boots:
		return ItemCategoryBoots;

	case EItemType::Bow:
		return ItemCategoryBow;

	case EItemType::Gloves:
		return ItemCategoryGloves;

	case EItemType::Helment:
		return ItemCategoryHelment;

	case EItemType::Leg:
		return ItemCategoryLeg;

	case EItemType::Mace:
		return ItemCategoryMace;

	case EItemType::Sword:
		return ItemCategorySword;

	case EItemType::Shield:
		return ItemCategoryShield;

	case EItemType::Ring:
		return ItemCategoryRing;

	case EItemType::Neck:
		return ItemCategoryNeck;

	default:
		return ItemCategoryNone;
	}
}

FText UFL_ItemHelper::GetItemSubTypeName(const EItemSubType& Category)
{
	switch (Category)
	{
	case EItemSubType::Heavy:
		return ItemCategoryHeavy;

	case EItemSubType::Light:
		return ItemCategoryLight;

	case EItemSubType::Medium:
		return ItemCategoryMedium;

	default:
		return ItemCategoryNone;
	}
}

template<typename T>
inline TArray<T> UFL_ItemHelper::GetEnumList()
{
	TArray<T> AllEnumValues;
	UEnum* Enum = StaticEnum<T>();
	if (Enum)
	{
		for (int i = 0; i < Enum->NumEnums() - 1; i++)
		{
			T Value = static_cast<T>(Enum->GetValueByIndex(i));
			AllEnumValues.Add(Value);
		}
	}
	return AllEnumValues;
}

TArray<EItemCategory> UFL_ItemHelper::GetItemCategories()
{
	return GetEnumList<EItemCategory>();
}




