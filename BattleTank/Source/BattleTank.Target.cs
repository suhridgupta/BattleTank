// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTankTarget : TargetRules
{
	//public BattleTankTarget(TargetInfo Target)
	public BattleTankTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.Add("BattleTank");
	}

	//
	// TargetRules interface.
	//

	/*public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "BattleTank" } );
	}*/
}
