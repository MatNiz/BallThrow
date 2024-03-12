// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BallThrow : ModuleRules
{
	public BallThrow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "UMG",
            "Slate",
            "SlateCore",
            "Niagara"});
    }
}