#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/DTReader.h"
#include "PlaygroundWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UPlaygroundWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    /** 初始化函数（重写虚函数） */
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UDataTable> MyDialogue;

    int32 TextIndex;
    int32 InvesIndex = -1;

    TArray<FDialogData*>Dialogues;

    /** 文本框按钮 */
    UPROPERTY(meta = (BindWidget))
    class UButton* TextBubble;

    /** 对话文本 */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DialogueText;

    /** 立绘放置面板 */
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* PortraitsPlacement;

    /** 各个立绘的图像控件 */
    UPROPERTY(meta = (BindWidget))
    class UImage* Naegi_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Asahina_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Mondo_Angry;

    UPROPERTY(meta = (BindWidget))
    class UImage* Sayaka_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Yamada_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Hagakure_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_laugh;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_thread;

    UPROPERTY(meta = (BindWidget))
    class UImage* Kirigiri_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Leon_normal;

    /** 控制立绘的显示和隐藏 */
    void SetTextAndBubbleHidden();
    void SetTextAndBubbleVisible();
    void SetPortraitVisible();
    void SetPortraitHidden();
    void InitializePortraits();
    UFUNCTION()
    void OnBubbleClicked();
    TObjectPtr<UDataTable> CurrentDialogue;
    TObjectPtr<UImage> CurrentPortrait;

    bool EndMap = false;
    TArray<FName>_rowNames;
};

