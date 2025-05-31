// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_ItemHelper.h"
#include "Math/UnrealMathUtility.h"
#include "..\Public\FL_ItemHelper.h"


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

bool UFL_ItemHelper::ItemEffectsIsIqual(const TArray<FEffectStatus>& FirstEffects, const TArray<FEffectStatus>& SecondEffects)
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
		OutResult = EExecResult::Valid;
		Item = ItemsDA->Items[ID];
	}

	OutResult = EExecResult::NotValid;
	Item = FItemAbstract();
}



