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
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FInventorySystemEditorModule::RegisterBlueprintMenuExtension));


	/*FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	BlueprintEditorModule.OnGatherBlueprintMenuExtensions().AddRaw(this, &FInventorySystemEditorModule::RegisterBlueprintMenuExtension);*/
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

void FInventorySystemEditorModule::RegisterBlueprintMenuExtension()
{
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(
		"GraphEditor.GraphNodeContextMenu.K2Node_CallFunction");
	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("Test");

	/*ToolbarSection.AddEntry(FToolMenuEntry::InitWidget(

	));*/
	ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
		TEXT("ItemsEditor"),
		FExecuteAction::CreateLambda([]()
			{


			}),
			INVTEXT("Find in quest"),
			INVTEXT("Find in quest"),
			FSlateIcon(FName("EditorStyle"), "MainFrame.VisitSearchForAnswersPage")
			));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInventorySystemEditorModule, InventorySystemEditor)