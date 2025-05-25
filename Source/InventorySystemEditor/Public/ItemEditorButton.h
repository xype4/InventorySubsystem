#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateIconFinder.h" 


#define LOCTEXT_NAMESPACE "FItemEditorButton"

class FItemEditorButton : public TCommands<FItemEditorButton>

{
	public:

		FItemEditorButton() : TCommands(TEXT("MyToolbarButton"), FText::FromString("My Toolbar Button Plugin"), NAME_None, FEditorStyle::GetStyleSetName()) {}

		TSharedPtr<FUICommandInfo> ItemEditorButtonCommand;

		virtual void RegisterCommands() override;

	public:

		static void OnClickedButton();

		static FText GetButtonName()
		{
			return LOCTEXT("ItemEditorButtonName", "ItemEditor");
		}

		static FText GetButtonTooltip()
		{
			return LOCTEXT("ItemEditorButtonTooltip", "Edit Items Instance DataBase");
		}

		static FSlateIcon GetButtonIcon()
		{
			return FSlateIcon(GetStylename(), "InventoryPlugin.ItemEditorIcon");
		}

	private:

		static FName GetStylename()
		{
			return FName("InventoryPluginStyle");
		}
};

#undef LOCTEXT_NAMESPACE

