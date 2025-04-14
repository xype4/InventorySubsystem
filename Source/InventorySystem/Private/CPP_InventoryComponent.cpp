

#include "CPP_InventoryComponent.h"

UCPP_InventoryComponent::UCPP_InventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UCPP_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ItemsDataTable == nullptr)
	{
		
		UE_LOG(LogTemp, Error, TEXT("База данных предметов не задана для %s"), *GetOwner()->GetName());
	}

}


void UCPP_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

const int UCPP_InventoryComponent::GetSlotsCount()
{
	return SlotsCount;
}

TArray<FItemInstance> UCPP_InventoryComponent::SetSlotsCount(const int NewCount, EWhenInventuryOverflow& isOverflowed)
{
	if (NewCount >= SlotsCount)
	{
		SlotsCount = NewCount;
		isOverflowed = EWhenInventuryOverflow::Exec;
		return TArray<FItemInstance>();
	}

	else
	{


		TArray<FItemInstance> OverflowedItems;
		int DeltaSlots = NewCount - SlotsCount;

		for (int i = Items.Num() - 1; i >= NewCount; i--)
		{
			OverflowedItems.Add(Items[i]);
		}

		Items.SetNum(NewCount);

		isOverflowed = EWhenInventuryOverflow::Overflowed;
		return OverflowedItems;
	}
}

FItemInstance UCPP_InventoryComponent::AddItem(const FItemInstance Item, EWhenInventuryOverflow& isOverflowed)
{
	if (ItemsDataTable != nullptr)
	{
		int CountToAdd = Item.Count;

		//Попытка добавить к существующим стакам
		for (int i = 0; i < Items.Num(); i++) {
			if (Items[i].ItemAbstract.ItemID == Item.ItemAbstract.ItemID)
			{
				if (UFL_ItemHelper::ItemsEqual(Items[i].ItemAbstract, Item.ItemAbstract) == EItemsEqual::FullEqual)
				{
					if (Items[i].Count < MaxStack)
					{
						int FreeSpace = MaxStack - Items[i].Count;
						if(FreeSpace>= CountToAdd)
						{
							Items[i].Count += Item.Count;
							isOverflowed = EWhenInventuryOverflow::Exec;
							return FItemInstance();
						}
						else
						{
							Items[i].Count += FreeSpace;
							CountToAdd -= FreeSpace;
						}
					}							
				}
			}
		}

		//Попытка добавить в пустые ячейки
		while(CountToAdd > 0)
		{
			if (Items.Num() < SlotsCount)
			{
				if (CountToAdd > MaxStack)
				{
					CountToAdd -= MaxStack;
					Items.Add(FItemInstance(Item.ItemAbstract, MaxStack));
				}
				else
				{
					Items.Add(FItemInstance(Item.ItemAbstract, CountToAdd));
					CountToAdd = 0;
				}
			}
			else
			{
				isOverflowed = EWhenInventuryOverflow::Overflowed;
				return FItemInstance(Item.ItemAbstract, CountToAdd);
			}
		}
		isOverflowed = EWhenInventuryOverflow::Exec;
		return FItemInstance();
	}
	else
	{
		isOverflowed = EWhenInventuryOverflow::Error;
		return FItemInstance();
	}
}

bool UCPP_InventoryComponent::RemoveItemByInstance(const FItemInstance Item)
{
	int CountToRemove = Item.Count;

	for (int i = 0; i < Items.Num(); i++) {
		if (Items[i].ItemAbstract.ItemID == Item.ItemAbstract.ItemID)
		{
			if (UFL_ItemHelper::ItemsEqual(Items[i].ItemAbstract, Item.ItemAbstract) == EItemsEqual::FullEqual)
			{
				if (Items[i].Count <= CountToRemove)
				{
					CountToRemove -= Items[i].Count;
					Items.RemoveAtSwap(i);
					if (CountToRemove == 0)
						return true;

					continue;
				}
				else
				{
					Items[i].Count -= CountToRemove;
					return true;
				}
			}
		}
		i++;
	}

	return false;
}

bool UCPP_InventoryComponent::RemoveItemByID(int id, int count)
{
	int CountToRemove = count;

	for (int i = 0; i < Items.Num();) {
		if (Items[i].ItemAbstract.ItemID == id)
		{
			if (Items[i].Count <= CountToRemove)
			{
				CountToRemove -= Items[i].Count;
				Items.RemoveAtSwap(i);
				if (CountToRemove == 0)
					return true;

				continue;	
			}
			else
			{
				Items[i].Count -= CountToRemove;
				return true;
			}
		}
		i++;
	}

	return false;
}

const TArray<FItemInstance> UCPP_InventoryComponent::GetItems()
{
	return Items;
}

const TArray<FItemInstance> UCPP_InventoryComponent::GetItemsByCategory(const EItemCategory Category)
{
	TArray<FItemInstance> ReturnedItems;

	for (int i = 0; i < Items.Num(); i++) {
		if (Items[i].ItemAbstract.ItemCategory == Category)
		{
			ReturnedItems.Add(Items[i]);
		}
	}
	return ReturnedItems;
}
