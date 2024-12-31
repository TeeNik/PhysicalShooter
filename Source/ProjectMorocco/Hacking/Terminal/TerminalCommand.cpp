// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalCommand.h"

void UTerminalCommand::Execute()
{
	ExecuteImplementation();
	BP_ExecuteImplementation();
}

void UTerminalCommand::ExecuteImplementation()
{
}
