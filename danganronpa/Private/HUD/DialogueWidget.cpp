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
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues已获取DataTable所有行信息
		FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false代表不报错
		// 更新文本框内容
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}
}

void UDialogueWidget::OnBubbleClicked()
{
	if (bIsAnimating) {
		// 如果正在播放动画，直接返回，避免重复触发
		UE_LOG(LogTemp, Warning, TEXT("Animation is in progress. Ignoring further clicks."));
		return;
	}

	if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			SetTextAndBubbleHidden();

			if (InMainDialogue) {
				if (TextIndex == 2) {
					InvestigatePhase = true;
				}
				if (TextIndex == Dialogues.Num() - 1 && InvestigatePhase && PaperRead && CameraRead) {
					PlayAnimate();
					InvestigatePhase = false;
				}
				else if (TextIndex == 3) {
					bIsAnimating = true; // 标记动画正在播放

					// 播放隐藏动画
					PlayAnimation(BroadcastFade);
					SetTextAndBubbleHidden();

					// 延迟切换到 MyDialogue 的第三句话
					GetWorld()->GetTimerManager().SetTimer(
						TimerHandle1,
						[this]() {
							// 显示第三句话
							TextIndex = 4;
							DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));

							// 播放显示动画并显示对话框
							SetTextAndBubbleVisible();
							SetPortraitVisible();
							// 动画播放完成，重置标记
							bIsAnimating = false;
						},
						2.0f, // 延迟 1 秒
						false
					);
				}
				else if (TextIndex == 4) {
					// 对话结束，切换到新的关卡
					TextIndex = -1;
					UE_LOG(LogTemp, Warning, TEXT("Dialogue Finished. Loading Map_Playground..."));
					UGameplayStatics::OpenLevel(this, FName("FirstPersonMap"));
				}
			}
		}
		// 如果有新立绘
		else if (Dialogues[TextIndex + 1]->intro) {
			SetPortraitHidden();
			TextIndex++;
			SetPortraitVisible();
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}
		// 正常显示下一句
		else {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}
	}
	else if (InvestigatePhase) {
		// ...
	}
	else {

	}
}




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

		// 播放动画逻辑由 OnBubbleClicked 继续处理
	}
}




void UDialogueWidget::PlayAnimate()
{
	if (PaperRead && CameraRead) {
		TextMoveOn(0.0f); // 延迟处理其他逻辑
	}
}



void UDialogueWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//按钮不可见且不可交互
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
	// 确保 TextIndex 定位到编号为 3 的对话
	int32 TargetIndex = 3;

	// 检查 Dialogues 是否有效并包含索引为 3 和 4 的内容
	if (MyDialogue) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		MyDialogue->GetAllRows(ContextString, Dialogues);

		if (Dialogues.IsValidIndex(TargetIndex) && Dialogues.IsValidIndex(TargetIndex + 1)) {
			// 显示第 3 行对话
			TextIndex = TargetIndex;
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));

			// 播放出现动画并显示对话框
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
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}





