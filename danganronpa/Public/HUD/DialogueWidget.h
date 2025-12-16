#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DTReader.h"
#include "TimerManager.h"
#include "DialogueWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MyDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> CameraDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> DrawerDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> PaperDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BroadcastAppear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BroadcastFade;



	// 绑定的TextBlock
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;
	int32 TextIndex;
	int32 InvesIndex = -1;
	TArray<FDialogData*>Dialogues;
	TArray<FDialogData*>Dialogues_Inves;
	// TextBubble 控件
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TextBubble;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Camera;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Paper;

	// 各种角色立绘
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Naegi_normal;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Naegi_talking;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Naegi_confused;

	// Classroom背景
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Classroom;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Broadcast;

protected:
	UFUNCTION()
	void OnBubbleClicked();

	UFUNCTION()
	void OnCameraClicked();

	UFUNCTION()
	void OnPaperClicked();


private:
	bool InMainDialogue = true;
	bool InvestigatePhase = false;
	bool PaperRead = false;
	bool CameraRead = false;
	bool bIsAnimating = false;
	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();
	//获取定时器管理器
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	void InitializePortraits();
	//让文本框重新出现且内容往前，delay为出现的延迟时间
	void TextMoveOn(float delay);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();
	void PlayAnimate();
	TObjectPtr<UDataTable> CurrentDialogue;
};
