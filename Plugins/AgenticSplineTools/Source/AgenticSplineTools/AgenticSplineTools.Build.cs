// Copyright (c) 2024

using UnrealBuildTool;

public class AgenticSplineTools : ModuleRules
{
    public AgenticSplineTools(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new[]
            {
                "Core",
                "CoreUObject",
                "Engine"
            });
    }
}
