#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FInventorySystemStyle final
{

public:
	static void InitializeStyle();
	static void ShutdownStyle();

    static ISlateStyle& Get()
    {
        return *StyleSet.Get();
    }

    static FName GetStyleSetName();

    private:

        static FString RootToPluginContentDir(const FString& RelativePath, const TCHAR* Extension);

        static TUniquePtr<FSlateStyleSet> StyleSet;

};
