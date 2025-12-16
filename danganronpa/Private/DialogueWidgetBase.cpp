#include "DialogueWidgetBase.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<GeneralController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"
#include"HUD/KototamaWidget.h"
#include<GeneralController.h>
#include "Kismet/GameplayStatics.h"
void UDialogueWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Dialogues.Empty();
	InitializePortraits();
	TextIndex = 0;

	if (MainDialogue)
	{
		MainDialogue->GetAllRows("TEST", Dialogues);//Dialogues已获取DataTable所有行信息
		UE_LOG(LogTemp, Warning, TEXT("Dialogues array size: %d"), Dialogues.Num());
		if (Dialogues.IsValidIndex(0)) {
			UE_LOG(LogTemp, Warning, TEXT("happened"));
			FDialogData* _data = MainDialogue->FindRow< FDialogData>("1", "TEST", false);//false代表不报错
			// 更新文本框内容
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("What's happened"));
}

void UDialogueWidgetBase::OnBubbleClicked()
{
	if (EndMap) {
		//此处切换关卡
	}
	if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {//这样设置，TextIndex会停在out为true的地方
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			//执行隐藏/销毁函数
			SetTextAndBubbleHidden();

		}
		else if (Dialogues[TextIndex + 1]->intro) {//有新立绘要显示
			SetPortraitHidden();//隐藏先前立绘
			TextIndex++;
			//UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
			SetPortraitVisible();
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}
		else {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}

	}
}

void UDialogueWidgetBase::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//按钮不可见且不可交互
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidgetBase::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidgetBase::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UDialogueWidgetBase::OnBubbleClicked);
	}
}

void UDialogueWidgetBase::TextMoveOn(float delay)
{
	if (Dialogues[TextIndex + 1]->intro) {
		++TextIndex;
		UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UDialogueWidgetBase::SetPortraitVisible, delay, false);
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UDialogueWidgetBase::SetTextAndBubbleVisible, delay, false);
}

void UDialogueWidgetBase::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible!"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidgetBase::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}


