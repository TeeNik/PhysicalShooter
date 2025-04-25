// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ProjectMorocco/GameMode/HackingGameStateComponent.h"
#include "ProjectMorocco/GameMode/PMGameStateBase.h"
#include "ProjectMorocco/Hacking/Terminal/TerminalCommand.h"

void UTerminalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConsoleInput->OnTextCommitted.AddUniqueDynamic(this, &ThisClass::OnInputCommited);

	GetWorld()->GetGameState<APMGameStateBase>()->GetHackingGameStateComponent()->OnCommandExecuted.AddUniqueDynamic(this, &UTerminalWidget::OnCommandExecuted);
}

void UTerminalWidget::OnInputCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter)
	{
		ConsoleInput->SetText(FText::GetEmpty());
		GetWorld()->GetGameState<APMGameStateBase>()->GetHackingGameStateComponent()->ExecuteCommand(Text.ToString());

		if (TextScroll)
		{
			TextScroll->ScrollToEnd();
		}
	}
}

void UTerminalWidget::OnCommandExecuted(const FTerminalCommandResult& Result)
{
	FStringBuilderBase StringBuilder;
	StringBuilder.Append(ConsoleOutput->GetText().ToString());
	StringBuilder.Append(Result.Output);
	ConsoleOutput->SetText(FText::FromString(StringBuilder.ToString()));
}
