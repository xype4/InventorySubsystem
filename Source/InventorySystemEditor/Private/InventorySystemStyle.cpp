#include "InventorySystemStyle.h"

#include "Styling/CoreStyle.h"
#include "Styling/SlateTypes.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TUniquePtr<FSlateStyleSet> FInventorySystemStyle::StyleSet;

void FInventorySystemStyle::InitializeStyle()
{
    if (StyleSet.IsValid())
    {
        return;
    }

    StyleSet = MakeUnique<FSlateStyleSet>(GetStyleSetName());


    StyleSet->Set("Inventory.MyImage", new FSlateVectorImageBrush(RootToPluginContentDir("Textures/ItemEditorIcon32", TEXT(".svg")), FVector2D(32.0f, 32.0f)));


    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FInventorySystemStyle::ShutdownStyle()
{
    if (StyleSet.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
        StyleSet.Reset();
    }
}

FString FInventorySystemStyle::RootToPluginContentDir(const FString& RelativePath, const TCHAR* Extension)
{
    static const FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("InventorySystem"))->GetContentDir();
    return (ContentDir / RelativePath) + Extension;
}

FName FInventorySystemStyle::GetStyleSetName()
{
    static const FName StyleSetName(TEXT("InventorySystemStyle"));
    return StyleSetName;
}