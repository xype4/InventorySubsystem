// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandList.h"



class FInventorySystemEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() {};

	

protected:

	void AddToolbarButton(FToolBarBuilder& Builder);
	TSharedRef<FExtender> OnExtendLevelEditorToolbar(const TSharedRef<FUICommandList>& CommandList);

	TSharedPtr<FUICommandList> PluginCommands;
	TSharedPtr<FExtender> ToolbarExtender; 

private:
	void CreateItemEditorButton();
	void CreateSlateStyle();
};
