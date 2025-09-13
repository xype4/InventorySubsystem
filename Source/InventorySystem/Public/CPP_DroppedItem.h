// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_InteractiveItem.h"
#include "..\Public\FL_ItemHelper.h"

#include "CPP_DroppedItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API ACPP_DroppedItem : public ACPP_InteractiveItem
{
	GENERATED_BODY()

public:
	ACPP_DroppedItem();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Переопределённый меш (только на карте, в инвентарь добавится с базовым)"))
	UStaticMesh* OverrideMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Переопределённый материал (только на карте, в инвентарь добавится с базовым)"))
	UMaterialInstance* OverrideMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ClampMin = 0, UIMin = 0, ToolTip = "ИД предмета"))
	int ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ClampMin = 0, UIMin = 0, ToolTip = "Количество предметов"))
	int Count;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public", meta = (ToolTip = "Получить предмет"))
	FItemInstance GetContainItem();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Config", meta = (ToolTip = "Предмет"))
	FItemAbstract Item;

	virtual void OnInteract() override;

protected:

	UDA_Item* LoadedDataAsset;
	UStaticMesh* GetItemMesh();
	UMaterialInstance* GetItemMaterial();
	EExecResult IsValidItem;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual FText GetObjectName() override;
};
