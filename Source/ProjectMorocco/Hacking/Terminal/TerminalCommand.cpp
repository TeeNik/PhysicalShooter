// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalCommand.h"

FTerminalCommandResult UTerminalCommand::Execute()
{
	return RunCommandLogic();
}

FTerminalCommandResult UTerminalCommand::RunCommandLogic_Implementation()
{
	FTerminalCommandResult Result;
	Result.Output = FString::Printf(TEXT("%s\r\n"), *CommandName);
	return Result;
}
