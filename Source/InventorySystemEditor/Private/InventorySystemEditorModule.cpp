#include "InventorySystemEditorModule.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyleSet.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Styling/ISlateStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "ItemEditorButton.h"
#include "Styling/SlateIconFinder.h"



#define LOCTEXT_NAMESPACE "FInventorySystemEditorModule"

TSharedPtr<FSlateStyleSet> StyleSet;


void FInventorySystemEditorModule::StartupModule()
{
	CreateSlateStyle();
	CreateItemEditorButton();
}

void FInventorySystemEditorModule::ShutdownModule()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->RemoveExtender(ToolbarExtender);


	FItemEditorButton::Unregister();
}

void FInventorySystemEditorModule::AddToolbarButton(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(
		FItemEditorButton::Get().ItemEditorButtonCommand,
		NAME_None,
		FItemEditorButton::GetButtonName(),
		FItemEditorButton::GetButtonTooltip(),
		FItemEditorButton::GetButtonIcon());
}

TSharedRef<FExtender> FInventorySystemEditorModule::OnExtendLevelEditorToolbar(const TSharedRef<FUICommandList>& CommandList)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender());

	Extender->AddToolBarExtension(
		"Settings", // Location
		EExtensionHook::After,
		CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FInventorySystemEditorModule::AddToolbarButton)
	);

	return Extender;
}

void FInventorySystemEditorModule::CreateItemEditorButton()
{
	FItemEditorButton::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FItemEditorButton::Get().ItemEditorButtonCommand,
		FExecuteAction::CreateLambda([]()
			{
				FItemEditorButton::OnClickedButton();
			}),
		FCanExecuteAction());


	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	ToolbarExtender = MakeShareable(new FExtender);


	FToolBarExtensionDelegate ToolbarDelegate;
	ToolbarDelegate.BindLambda([this](FToolBarBuilder& Builder)
		{
			Builder.AddToolBarButton(
				FItemEditorButton::Get().ItemEditorButtonCommand,
				NAME_None,
				FItemEditorButton::GetButtonName(),
				FItemEditorButton::GetButtonTooltip(),
				FItemEditorButton::GetButtonIcon());
		});

	ToolbarExtender->AddToolBarExtension(
		"Settings",
		EExtensionHook::After,
		PluginCommands,
		ToolbarDelegate
	);

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FInventorySystemEditorModule::CreateSlateStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet("InventoryPluginStyle"));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / "InventorySystem/Resources");

	FString IconPath = StyleSet->RootToContentDir("ItemEditorIcon32", TEXT(".png"));

	FSlateImageBrush* MyIconButtonBrush = new FSlateImageBrush(IconPath, FVector2D(32, 32));

	StyleSet->Set("InventoryPlugin.ItemEditorIcon", MyIconButtonBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInventorySystemEditorModule, InventorySystemEditor)