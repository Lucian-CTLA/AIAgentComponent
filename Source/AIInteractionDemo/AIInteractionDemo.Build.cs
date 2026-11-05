// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIInteractionDemo : ModuleRules
{
	public AIInteractionDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AIInteractionDemo",
			"AIInteractionDemo/Variant_Platforming",
			"AIInteractionDemo/Variant_Platforming/Animation",
			"AIInteractionDemo/Variant_Combat",
			"AIInteractionDemo/Variant_Combat/AI",
			"AIInteractionDemo/Variant_Combat/Animation",
			"AIInteractionDemo/Variant_Combat/Gameplay",
			"AIInteractionDemo/Variant_Combat/Interfaces",
			"AIInteractionDemo/Variant_Combat/UI",
			"AIInteractionDemo/Variant_SideScrolling",
			"AIInteractionDemo/Variant_SideScrolling/AI",
			"AIInteractionDemo/Variant_SideScrolling/Gameplay",
			"AIInteractionDemo/Variant_SideScrolling/Interfaces",
			"AIInteractionDemo/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
