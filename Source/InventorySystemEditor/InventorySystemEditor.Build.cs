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
                "InventorySystem",

                "UMGEditor",
                "UnrealEd", // ����������� ��� Editor �������
                "Slate",       // ��������� ���������
                "SlateCore",   // ��������� ���������
                "EditorStyle", // ����� ���������
                "InputCore",
                "CoreUObject",
                "Engine",
                "Projects",   //��� ������������� IPluginManager
                "ToolMenus",
                "Blutility",


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
                // ... �������� ����� ������, ������� ��� ������ ��������� ����������� ...
            }
        );
    }
}