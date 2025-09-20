// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_InteractiveItem.h"
#include "..\Public\FL_ItemHelper.h"

#include "CPP_DroppedItem.generated.h"


UENUM(BlueprintType)
enum class ECreateType : uint8
{
	ByID UMETA(DisplayName = "ByID"),
	ByItem UMETA(DisplayName = "ByItem")
};

UCLASS()
class INVENTORYSYSTEM_API ACPP_DroppedItem : public ACPP_InteractiveItem
{
	GENERATED_BODY()

public:
	ACPP_DroppedItem();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Способ создания объекта", ExposeOnSpawn = true))
	ECreateType ConstructType = ECreateType::ByID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Включена ли физика на старте", ExposeOnSpawn = true))
	bool EnablePhysicsOnStart = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ClampMin = 0, UIMin = 0, ToolTip = "ИД предмета, если отсутствует Item, то предмет ищется по ID", ExposeOnSpawn = true, EditConditionHides = "ConstructType == ECreateType::ByID"))
	int ID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Config", meta = (ToolTip = "Предмет", ExposeOnSpawn = true, EditConditionHides = "ConstructType == ECreateType::ByItem"))
	FItemAbstract Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ClampMin = 0, UIMin = 0, ToolTip = "Количество предметов", ExposeOnSpawn = true))
	int Count;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Переопределённый меш (только на карте, в инвентарь добавится с базовым)", ExposeOnSpawn = true))
	UStaticMesh* OverrideMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Переопределённый материал (только на карте, в инвентарь добавится с базовым)", ExposeOnSpawn = true))
	UMaterialInstance* OverrideMaterial;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public", meta = (ToolTip = "Получить предмет"))
	FItemInstance GetContainItem();

	virtual void OnInteract() override;

protected:

	UDA_Item* LoadedDataAsset;
	UStaticMesh* GetItemMesh();
	UMaterialInstance* GetItemMaterial();
	EExecResult IsValidItem;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual FText GetObjectName() override;
};
