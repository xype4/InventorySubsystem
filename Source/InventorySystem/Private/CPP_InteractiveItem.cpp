// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_InteractiveItem.h"

FText ACPP_InteractiveItem::GrabHint = NSLOCTEXT("Items", "ItemHintGrab", "Grab: ");
FText ACPP_InteractiveItem::InteractHint = NSLOCTEXT("Items", "ItemHintInteract", "Interact: ");

// Sets default values
ACPP_InteractiveItem::ACPP_InteractiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractType = EInteractTypes::Interact;

}

FString ACPP_InteractiveItem::GetHintText()
{
	switch (InteractType)
	{
	case EInteractTypes::Interact:
		return (InteractHint.ToString()+ GetObjectName().ToString());
		break;
	case EInteractTypes::Grab:
		return (GrabHint.ToString() + GetObjectName().ToString());
		break;
	default:
		break;
	}
	return "";
}

// Called when the game starts or when spawned
void ACPP_InteractiveItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_InteractiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

