#include "ItemEditorButton.h"

#include "Editor/EditorEngine.h"  
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Editor/Blutility/Public/IBlutilityModule.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"

#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"

#define LOCTEXT_NAMESPACE "ItemEditorButton"

void FItemEditorButton::RegisterCommands()
{
	UI_COMMAND(ItemEditorButtonCommand, "My Button", "Open My Menu", EUserInterfaceActionType::Button, FInputGesture());
}

void FItemEditorButton::OnClickedButton()
{
	auto findedPath = FSoftObjectPath("EditorUtilityWidgetBlueprint'/InventorySystem/ItemsEditor/EW_ItemsEditor.EW_ItemsEditor'");
	
	
	if (UWidgetBlueprint* Blueprint = Cast<UWidgetBlueprint>(findedPath.TryLoad())) 
	{
		if(Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{
			if(UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint))
			{
				UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
				EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
			}
		}
	}

}

#undef LOCTEXT_NAMESPACE