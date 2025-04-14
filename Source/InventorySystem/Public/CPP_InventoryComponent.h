// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_Item.h"
#include "FL_ItemHelper.h"
#include "Engine/DataTable.h"

#include "CPP_InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EWhenInventuryOverflow : uint8
{
	Exec				UMETA(DisplayName = "Exec"),
	Overflowed			UMETA(DisplayName = "Owerflowed"),
	Error				UMETA(DisplayName = "Error")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UCPP_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "База данных предметов"))
		UDataTable* ItemsDataTable;


	UPROPERTY(EditAnywhere, Category = "Config", meta = (ClampMin = "1", UIMin = "1", ToolTip = "Базовое количество слотов в инвентаре"))
		int SlotsCount = 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (ClampMin = "1", UIMin = "1", ToolTip = "Максимальное количество предметов в слоте"))
		int MaxStack = 128;

private:

	TArray<FItemInstance> Items;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public|Get", meta = (ToolTip = "Получение количества слотов инвентарного компонента"))
		const int GetSlotsCount();

	UFUNCTION(BlueprintCallable, Category = "Public|Set", meta = (ToolTip = "Установка нового количества слотов инвентаря с обработкой переполнения", ExpandEnumAsExecs = "isOverflowed"))
		TArray<FItemInstance> SetSlotsCount(const int NewCount, EWhenInventuryOverflow& isOverflowed);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Добавление нового предмета в инвентарь", ExpandEnumAsExecs = "isOverflowed"))
		FItemInstance AddItem(const FItemInstance Item, EWhenInventuryOverflow& isOverflowed);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Удаление конкретного предмета из инвентаря. Возвращает флаг были ли удалены предметы в запрашеваемом количестве"))
		bool RemoveItemByInstance(const FItemInstance Item);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Удаление любого предмета из инвентаря с совпадающим ID. Возвращает флаг были ли удалены предметы в запрашеваемом количестве"))
		bool RemoveItemByID(int id, int count);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public|Get", meta = (ToolTip = "Получение предметов из инвентаря"))
		const TArray<FItemInstance> GetItems();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public|Get", meta = (ToolTip = "Получение предметов из инвентаря с заданной категирией"))
		const TArray<FItemInstance> GetItemsByCategory(const EItemCategory Category);
};
