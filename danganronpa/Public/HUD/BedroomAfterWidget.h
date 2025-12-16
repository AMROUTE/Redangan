#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"DTReader.h"
#include "TimerManager.h"
#include "BedroomAfterWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UBedroomAfterWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>TextBubble;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>GoldenKatana;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Drawer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>ScratchOnFloor;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>MaizonoHand;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> B11037;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>BathRoomDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BedroomAfterFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BathroomFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>Flash;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MyDialogue;//                            DataTables

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> KototamaTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> KatanaDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> DrawerDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> ScratchDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> MaizonoHandDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> _11037Dialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> EndDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> InvesBathroom;

	// 绑定的TextBlock
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	int32 TextIndex;
	int32 InvesIndex = -1;

	int32 GetNum = 0;

	TArray<FDialogData*>Dialogues;
	TArray<FDialogData*>Dialogues_Inves;

	TArray<FName>KototamaNames;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Monokuma_BigLaugh;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_Firm;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_ThinkTalk;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_Idle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_Think;
protected:
	UFUNCTION()
	void OnBubbleClicked();

	UFUNCTION()
	void OnDoorClicked();

	UFUNCTION()
	void OnKatanaClicked();

	UFUNCTION()
	void OnScratchClicked();

	UFUNCTION()
	void OnDrawerClicked();

	UFUNCTION()
	void OnMaizonoHandClicked();

	UFUNCTION()
	void On11037Clicked();


private:
	bool LookForMaizono;
	bool EnterBathroomAgain = false;
	bool InBedroom;
	bool InBathroom;
	bool InMainDialogue = true;
	bool InvestigatePhase = false;
	bool EndMap = false;
	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();
	//获取定时器管理器
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	void InitializePortraits();
	//让文本框重新出现且内容往前，delay为出现的延迟时间
	void TextMoveOn(float delay = 4.0f);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();

	TObjectPtr<UDataTable> CurrentDialogue;


};
