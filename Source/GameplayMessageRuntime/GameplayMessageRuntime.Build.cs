// Copyright Epic Games, Inc. All Rights Reserved.
// See the LICENSE file for details.

using UnrealBuildTool;

public class GameplayMessageRuntime : ModuleRules
{
	public GameplayMessageRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;				

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"GameplayTags"
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
			});
	}
}
