#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"HUD/DTReader.h"
#include "DialogueWidgetBase.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UDialogueWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>TextBubble;

	// 绑定的TextBlock
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	int32 TextIndex;

	TArray<FDialogData*>Dialogues;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MainDialogue;//                            DataTables

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> KototamaTable;

	virtual void InitializePortraits();

	TArray<FName>_rowNames;

	UFUNCTION()
	virtual void OnBubbleClicked();



	//让文本框重新出现且内容往前，delay为出现的延迟时间
	void TextMoveOn(float delay = 4.0f);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();

	//获取定时器管理器
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;

	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();

	bool EndMap = false;
};
