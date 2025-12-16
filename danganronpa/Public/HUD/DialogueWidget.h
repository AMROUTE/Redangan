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
	int32 TextIndex = 0; // Ensure initialization
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

	// 各角色立绘
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

	// vvvvvv DECORATOR PATTERN MEMBERS vvvvvv
	struct IDlgStep;
	TUniquePtr<IDlgStep> RootStep; // 指向装饰器链的第一个环节
	struct FDlgContext;
	TUniquePtr<FDlgContext> Ctx;   // 运行时上下文
	void BuildPipeline();          // 用于组装装饰器链的函数
	// ^^^^^^ DECORATOR PATTERN MEMBERS ^^^^^^

	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();
	//获取计时器句柄
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	void InitializePortraits();
	//将文本框根据传入的delay为负值的延迟时间
	void TextMoveOn(float delay);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();
	void PlayAnimate();
	TObjectPtr<UDataTable> CurrentDialogue;
};


// ----------------- DECORATOR PATTERN IMPLEMENTATION (IN-FILE) -----------------

// 轻量上下文，用于在装饰器之间传递Widget指针
struct FDlgContext {
    class UDialogueWidget* Widget = nullptr;
};

// 所有对话“步骤”的接口
struct IDlgStep {
    virtual ~IDlgStep() {}
    virtual void Execute(FDlgContext& Ctx) = 0;
};

// 所有“包装器”或“装饰器”的基类
struct FDlgDecorator : public IDlgStep {
    TUniquePtr<IDlgStep> Inner; // 持有被包装的下一个步骤
    explicit FDlgDecorator(TUniquePtr<IDlgStep> In) : Inner(MoveTemp(In)) {}
    void Execute(FDlgContext& Ctx) override { if (Inner) Inner->Execute(Ctx); }
};

// 核心步骤：只负责显示下一句文本并推进索引
struct FCoreStep : public IDlgStep {
    void Execute(FDlgContext& Ctx) override;
};

// 装饰器 #1: 如果动画正在播放，则阻塞输入
struct FInputGuardDeco : public FDlgDecorator {
    using FDlgDecorator::FDlgDecorator;
    void Execute(FDlgContext& Ctx) override;
};

// 装饰器 #2: 处理当前行角色的立绘显示/隐藏
struct FPortraitDeco : public FDlgDecorator {
    using FDlgDecorator::FDlgDecorator;
    void Execute(FDlgContext& Ctx) override;
};
