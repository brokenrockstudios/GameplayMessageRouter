// Copyright Epic Games, Inc. All Rights Reserved.
// See the LICENSE file for details.

using UnrealBuildTool;

public class GameplayMessageNodes : ModuleRules
{
	public GameplayMessageNodes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"KismetCompiler",
				"PropertyEditor",
				"GameplayMessageRuntime",
				"UnrealEd"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"BlueprintGraph",
			}
		);
	}
}
