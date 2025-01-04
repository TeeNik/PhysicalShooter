// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"
#include "TerminalCommand.h"
#include "AssetRegistry/AssetRegistryModule.h"

void UTerminal::Initialize()
{
	CollectCommands();
}

void UTerminal::ExecuteCommand(const FString& String)
{
	FString Command = String.TrimStartAndEnd().ToLower();
	if (auto CommandClass = CommandsByName.FindRef(Command))
	{
		if (auto* CommandCDO = CommandClass->GetDefaultObject<UTerminalCommand>())
		{
			CommandCDO->Execute();
		}
	}
}

const TArray<UClass*>& UTerminal::GetAllCommands() const
{
	return CommandClasses;
}

void UTerminal::CollectCommands()
{
	TArray<UClass*> AllCommands;
	GetDerivedClasses(UTerminalCommand::StaticClass(), AllCommands, true);

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName).Get();
	TArray<FAssetData> Assets;
	AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetClassPathName(), Assets, true);

	for (const FAssetData& Asset : Assets)
	{
		const UBlueprint* BlueprintObj = Cast<UBlueprint>(Asset.GetAsset());
		if (!BlueprintObj)
		{
			continue;
		}
		
		UClass* BlueprintClass = BlueprintObj->GeneratedClass;
		if (!BlueprintClass || !BlueprintClass->IsChildOf(UTerminalCommand::StaticClass()))
		{
			continue;
		}

		AllCommands.AddUnique(BlueprintClass);
	}

	for(auto* Class : AllCommands)
	{
		if (Class->GetName().StartsWith(TEXT("SKEL_")) || Class->GetName().StartsWith(TEXT("REINST_")) || Class->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated))
		{
			continue;
		}
		CommandClasses.Add(Class);
	}

	for (auto* Class : CommandClasses)
	{
		if (auto* CDO = Class->GetDefaultObject<UTerminalCommand>())
		{
			CommandsByName.Add(CDO->CommandName, Class);
		}
	}
}
