#include "InventorySystemEditorModule.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FInventorySystemEditorModule"

void FInventorySystemEditorModule::StartupModule()
{
    // This code will execute after your module is loaded into memory;
    // add initialization logic here.
}

void FInventorySystemEditorModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up module data.
    // Clean up resources here.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInventorySystemEditorModule, InventorySystemEditor)