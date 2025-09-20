// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DroppedItem.h"

ACPP_DroppedItem::ACPP_DroppedItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	InteractType = EInteractTypes::Grab;
}

FItemInstance ACPP_DroppedItem::GetContainItem()
{
	FItemInstance ItemInst;

	if (IsValidItem == EExecResult::Valid)
	{
		ItemInst.ItemAbstract = Item;
		ItemInst.Count = Count;
	}
	return ItemInst;
}

UStaticMesh* ACPP_DroppedItem::GetItemMesh()
{

	if (Item.Mesh.IsValid())
	{
		return Item.Mesh.Get();
	}
	else
	{
		return Item.Mesh.LoadSynchronous();
	}
}

UMaterialInstance* ACPP_DroppedItem::GetItemMaterial()
{
	if (Item.Material.IsValid())
	{
		return Item.Material.Get();
	}
	else
	{
		return Item.Material.LoadSynchronous();
	}
}

void ACPP_DroppedItem::OnInteract()
{
	Super::OnInteract();
	Destroy();
}


void ACPP_DroppedItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	switch (ConstructType)
	{
	case ECreateType::ByID:
		
		if (!LoadedDataAsset)
			LoadedDataAsset = Cast<UDA_Item>(StaticLoadObject(UDA_Item::StaticClass(), nullptr, TEXT("/InventorySystem/ItemsEditor/DA_ItemsData.DA_ItemsData")));

		UFL_ItemHelper::GetItemByID(ID, LoadedDataAsset, IsValidItem, Item);
		break;

	case ECreateType::ByItem:

		ID = Item.ItemID;

		break;

	default:
		break;
	}

	if (auto mesh = GetItemMesh())
	{
		StaticMesh->SetStaticMesh(mesh);
	}

	if (auto material = GetItemMaterial())
	{
		StaticMesh->SetMaterial(0, material);
	}
	

	if(OverrideMesh)
	{
		StaticMesh->SetStaticMesh(OverrideMesh);
	}
	if (OverrideMaterial)
	{
		StaticMesh->SetMaterial(0, OverrideMaterial);
	}
	
	StaticMesh->SetSimulatePhysics(EnablePhysicsOnStart);
	StaticMesh->SetEnableGravity(EnablePhysicsOnStart);

}

FText ACPP_DroppedItem::GetObjectName()
{
	return Item.ItemName;
}
