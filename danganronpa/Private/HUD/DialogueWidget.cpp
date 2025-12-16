#include "HUD/DialogueWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"
#include"HUD/KototamaWidget.h"
#include "Kismet/GameplayStatics.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializePortraits();
	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");


	if (MyDialogue)
	{
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues已获取DataTable的所有信息
		FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false表示可选
		// 设置初始文本
		if (Dialogues.IsValidIndex(TextIndex))
        {
		    DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
        }
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}

    // vvvvvv NEW CODE vvvvvv
    BuildPipeline(); // 组装装饰器链
    Ctx = MakeUnique<FDlgContext>(); // 创建上下文对象
    Ctx->Widget = this; // 初始化上下文
    // ^^^^^^ NEW CODE ^^^^^^
}

// vvvvvv REFACTORED FUNCTION vvvvvv
void UDialogueWidget::OnBubbleClicked()
{
    // 复杂的逻辑现在被委托给装饰器链
    if (RootStep)
    {
        RootStep->Execute(*Ctx);
    }
}
// ^^^^^^ REFACTORED FUNCTION ^^^^^^


// --- UNCHANGED FUNCTIONS (FOR NOW) ---
// Note: The logic inside these functions can also be moved into decorators later.

void UDialogueWidget::OnCameraClicked()
{
	TextIndex = -1;
	CameraRead = true;
	if (InvestigatePhase) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		CameraDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}

}

void UDialogueWidget::OnPaperClicked()
{
	TextIndex = -1; // 重置对话索引
	PaperRead = true; // 标记 Paper 对话已读

	if (InvestigatePhase) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		PaperDialogue->GetAllRows(ContextString, Dialogues);

		// 显示 Paper 对话的第一句话
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
}

void UDialogueWidget::PlayAnimate()
{
	if (PaperRead && CameraRead) {
		TextMoveOn(0.0f); // 延迟触发后续逻辑
	}
}

void UDialogueWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//按钮不可见性也可以被设置
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidget::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UDialogueWidget::OnBubbleClicked);
	}
	Broadcast->SetRenderOpacity(0.0f);
	Naegi_normal->SetVisibility(ESlateVisibility::Hidden);
	Naegi_talking->SetVisibility(ESlateVisibility::Hidden);
	Naegi_confused->SetVisibility(ESlateVisibility::Hidden);
	Camera->SetRenderOpacity(0.0f);
	Camera->OnClicked.AddDynamic(this, &UDialogueWidget::OnCameraClicked);
	Paper->SetRenderOpacity(0.0f);
	Paper->OnClicked.AddDynamic(this, &UDialogueWidget::OnPaperClicked);
}

void UDialogueWidget::TextMoveOn(float delay)
{
	// 确保 TextIndex 定位到索引为 3 的对话
	int32 TargetIndex = 3;

	// 检查 Dialogues 是否有效并且索引为 3 和 4 的元素存在
	if (MyDialogue) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		MyDialogue->GetAllRows(ContextString, Dialogues);

		if (Dialogues.IsValidIndex(TargetIndex) && Dialogues.IsValidIndex(TargetIndex + 1)) {
			// 显示第 3 段对话
			TextIndex = TargetIndex;
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));

			// 播放动画并显示对话
			PlayAnimation(BroadcastAppear);
			SetTextAndBubbleVisible();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Target Index 3 or 4 is out of range in Dialogues!"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("MyDialogue is NULL! Cannot load dialogues."));
	}
}

void UDialogueWidget::SetPortraitVisible()
{
	if (!Dialogues.IsValidIndex(TextIndex)) return;

	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前说话者的名字
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::SetPortraitHidden()
{
    if (!Dialogues.IsValidIndex(TextIndex)) return;

	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前说话者的名字
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}


// ----------------- DECORATOR PATTERN IMPLEMENTATION (IN-FILE) -----------------

// vvvvvv NEW FUNCTIONS vvvvvv

void UDialogueWidget::BuildPipeline()
{
    // 组装装饰器链，顺序是：从内到外
    // 1. 核心是“显示文本并推进”
    TUniquePtr<IDlgStep> Core = MakeUnique<FCoreStep>();
    // 2. 用“立绘处理器”包裹核心
    TUniquePtr<IDlgStep> WithPortrait = MakeUnique<FPortraitDeco>(MoveTemp(Core));
    // 3. 最外层用“输入守卫”包裹，最先被调用
    TUniquePtr<IDlgStep> WithGuard = MakeUnique<FInputGuardDeco>(MoveTemp(WithPortrait));

    // 保存最外层的装饰器作为入口
    RootStep = MoveTemp(WithGuard);
}

// 核心步骤：显示文本并推进索引
void FCoreStep::Execute(FDlgContext& Ctx)
{
    if (!Ctx.Widget) return;
    UDialogueWidget* W = Ctx.Widget;

    // 检查索引是否有效
    if (W->Dialogues.IsValidIndex(W->TextIndex))
    {
        // 仅负责显示文本和推进索引
        W->DialogueText->SetText(FText::FromString(W->Dialogues[W->TextIndex]->DialogueText));
        W->TextIndex++; // 核心：索引+1
    }
    else
    {
        // 如果对话结束，可以加一个结束逻辑，这里暂时留空
        UE_LOG(LogTemp, Warning, TEXT("Dialogue ended or invalid index."));
        // Example: W->GetWorld()->GetFirstPlayerController<ADialoguePlayerController>()->EndDialogue();
    }
}

// 输入守卫：动画期间禁止推进
void FInputGuardDeco::Execute(FDlgContext& Ctx)
{
    if (!Ctx.Widget) return;
    // 如果正在播放动画，直接返回，不执行后续步骤
    if (Ctx.Widget->bIsAnimating)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input blocked by FInputGuardDeco."));
        return;
    }
    // 否则，正常执行内部包裹的步骤
    FDlgDecorator::Execute(Ctx);
}

// 立绘处理：显示和隐藏当前行的角色立绘
void FPortraitDeco::Execute(FDlgContext& Ctx)
{
    if (!Ctx.Widget) return;
    UDialogueWidget* W = Ctx.Widget;

    // 在执行核心步骤之前，显示立绘
    // 注意：这里简化了逻辑，没有处理 intro/out。可以后续添加为新的装饰器。
    W->SetPortraitVisible();

    // 执行内部包裹的步骤 (例如 FCoreStep)
    FDlgDecorator::Execute(Ctx);

    // 在核心步骤执行之后，可以隐藏立绘（如果需要的话）
    // W->SetPortraitHidden();
}
// ^^^^^^ NEW FUNCTIONS ^^^^^^
