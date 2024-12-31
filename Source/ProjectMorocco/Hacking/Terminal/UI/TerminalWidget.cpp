// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

void UTerminalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConsoleInput->OnTextCommitted.AddUniqueDynamic(this, &ThisClass::OnInputCommited);
}

void UTerminalWidget::OnInputCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter)
	{
		ConsoleInput->SetText(FText::GetEmpty());
	}
}
