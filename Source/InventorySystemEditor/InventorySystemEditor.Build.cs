using UnrealBuildTool;
using System.IO;

public class InventorySystemEditor : ModuleRules
{
    public InventorySystemEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                //"Core",
            }
        );

        PrivateIncludePaths.AddRange(
             new string[]
             {
             }
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine",
                "CoreUObject",
                "InputCore",
                "UnrealEd",

                "Slate",
                "SlateCore",
                "AssetTools",
                "ToolMenus",
                "EditorWidgets",
                "Blutility",
                "UMG",
                "UMGEditor",
                "GraphEditor",
                "DetailCustomizations",

                "PropertyEditor",
                "InventorySystem",
                "DataTableEditor",
                "LevelEditor",
                "EditorStyle",
                "AssetTools",
                "EditorWidgets",
                "BlueprintGraph",
                "AnimGraph",
                "ComponentVisualizers",
            }
        );

        PrivateIncludePaths.Add("Resources");                                        
        AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... добавьте любые модули, которые ваш модуль загружает динамически ...
            }
        );
    }
}