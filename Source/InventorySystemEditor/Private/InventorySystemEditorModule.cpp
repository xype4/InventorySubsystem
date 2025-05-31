#include "InventorySystemEditorModule.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
#include "InventorySystemStyle.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#include "WidgetBlueprint.h"
#include "Editor/Blutility/Public/IBlutilityModule.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"

#define LOCTEXT_NAMESPACE "FInventorySystemEditorModule"

TSharedPtr<FSlateStyleSet> StyleSet;


void FInventorySystemEditorModule::StartupModule()
{
	FInventorySystemStyle::InitializeStyle();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FInventorySystemEditorModule::RegisterMenuExtensions));
}

void FInventorySystemEditorModule::ShutdownModule()
{
	FInventorySystemStyle::ShutdownStyle();


	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}


void FInventorySystemEditorModule::RegisterMenuExtensions()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(
		"LevelEditor.LevelEditorToolBar.AssetsToolBar");
	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("File");

	ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
		TEXT("ItemsEditor"),
		FExecuteAction::CreateLambda([]()
			{
				UE_LOG(LogTemp, Log, TEXT("Try item editor open"));

				auto findedPath = FSoftObjectPath("EditorUtilityWidgetBlueprint'/InventorySystem/ItemsEditor/EW_ItemsEditorNew.EW_ItemsEditorNew'");
				if (UWidgetBlueprint* Blueprint = Cast<UWidgetBlueprint>(findedPath.TryLoad()))
				{
					if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
					{
						if (UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint))
						{
							UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
							EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Not find EditorWidget"));
				}

			}),
		INVTEXT("Items Editor button"),
		INVTEXT("Open Items editor "),
		FSlateIcon(FInventorySystemStyle::GetStyleSetName(), "Inventory.MyImage")
	));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInventorySystemEditorModule, InventorySystemEditor)