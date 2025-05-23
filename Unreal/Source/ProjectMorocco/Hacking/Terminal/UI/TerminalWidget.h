#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "TerminalWidget.generated.h"

class UScrollBox;
struct FTerminalCommandResult;
class UTextBlock;
class UEditableText;

UCLASS()
class PROJECTMOROCCO_API UTerminalWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnInputCommited(const FText& Text, ETextCommit::Type CommitMethod);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ConsoleInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ConsoleOutput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScrollBox* TextScroll;
	
	UFUNCTION()
	void OnCommandExecuted(const FTerminalCommandResult& Result);
};
