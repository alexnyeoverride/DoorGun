using UnrealBuildTool;

public class DoorGunShaders : ModuleRules
{
	public DoorGunShaders(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(new[]
		{
			"DoorGunShaders/Private"
		});
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("TargetPlatform");
		}
		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("Engine");
		PublicDependencyModuleNames.Add("MaterialShaderQualitySettings");
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Renderer",
			"RenderCore",
			"RHI",
			"Projects"
		});
		
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new[] {
					"UnrealEd",
					"MaterialUtilities",
					"SlateCore",
					"Slate"
				}
			);
		}
	}
}