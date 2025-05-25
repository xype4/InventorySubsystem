// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_Item.h"

TArray<FItemAbstract>* UDA_Item::GetItemsP()
{
    return &Items;
}

void UDA_Item::AddNewItem()
{
    Items.Add(FItemAbstract());
    int LastId = 0;
    if(Items.Num()>=2)
        LastId = Items[Items.Num() - 2].ItemID;

    Items[Items.Num() - 1].ItemID = LastId+1;
}

bool UDA_Item::RemoveItem(int id)
{
    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if (Items[i].ItemID == id)
        {
            Items.RemoveAtSwap(i);
            return true;
        }
    }
    return false;
}

bool UDA_Item::GetItem(int id, FItemAbstract& Item)
{
    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if (Items[i].ItemID == id)
        {
            Item = Items[i];
            return true;
        }
    }
    return false;
}

bool UDA_Item::ReplaceItemByID(FItemAbstract NewItem)
{
    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if(Items[i].ItemID == NewItem.ItemID)
        {
            Items[i] = NewItem;
            return true;
        }
    }
    return false;
}

void UDA_Item::GetItems(TArray<FItemAbstract>& ItemsRef)
{
    ItemsRef = Items;
    return;
}
