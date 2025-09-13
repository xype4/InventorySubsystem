// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_InteractiveItem.generated.h"

UENUM(BlueprintType)
enum class EInteractTypes : uint8
{
	Interact UMETA(DisplayName = "Interact"),
	Grab UMETA(DisplayName = "Grab")
};

UCLASS()
class INVENTORYSYSTEM_API ACPP_InteractiveItem : public AActor
{
	GENERATED_BODY()
	
public:		
	ACPP_InteractiveItem();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	EInteractTypes InteractType;

	UFUNCTION(BlueprintCallable, Category = "Public")
	virtual void OnTouch(bool startTouch) {};

	UFUNCTION(BlueprintCallable, Category = "Public")
	virtual void OnInteract() {};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Public", meta = (ToolTip = "Получить имя предмета"))
	FString GetHintText();

	static FText GrabHint;
	static FText InteractHint;

protected:
	virtual void BeginPlay() override;

	virtual FText GetObjectName() {return FText::FromString(""); };

public:	
	virtual void Tick(float DeltaTime) override;

};
