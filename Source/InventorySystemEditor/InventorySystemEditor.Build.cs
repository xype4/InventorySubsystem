using UnrealBuildTool;

public class InventorySystemEditor : ModuleRules
{
    public InventorySystemEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", //  Обычно нужен, если не был добавлен ранее
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd", // Необходимо для редакторских функций
                "PropertyEditor", // Для отображения свойств в редакторе
                "InventorySystem", // Зависимость от основного модуля
                "DataTableEditor",
            }
        );
    }
}