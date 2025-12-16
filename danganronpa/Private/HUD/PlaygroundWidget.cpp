#include "HUD/PlaygroundWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Kismet/GameplayStatics.h"
void UPlaygroundWidget::NativeOnInitialized()
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
		_rowNames = MyDialogue->GetRowNames();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}
}

void UPlaygroundWidget::OnBubbleClicked()
{
	if (EndMap) {
		UGameplayStatics::OpenLevel(this, FName("FirstPersonMap"));//此处切换关卡
	}
	if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			SetTextAndBubbleHidden();

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
			SetPortraitHidden();
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}
	}
	if (_rowNames[TextIndex] == FName(TEXT("EndOfDialogue"))) {
		EndMap = true;
	}
}


void UPlaygroundWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//按钮不可见且不可交互
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UPlaygroundWidget::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}

void UPlaygroundWidget::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UPlaygroundWidget::OnBubbleClicked);
	}
	Naegi_normal->SetVisibility(ESlateVisibility::Hidden);
	Asahina_normal->SetVisibility(ESlateVisibility::Hidden);
	Mondo_Angry->SetVisibility(ESlateVisibility::Hidden);
	Sayaka_normal->SetVisibility(ESlateVisibility::Hidden);
	Yamada_normal->SetVisibility(ESlateVisibility::Hidden);
	Hagakure_normal->SetVisibility(ESlateVisibility::Hidden);
	Monokuma_normal->SetVisibility(ESlateVisibility::Hidden);
	Monokuma_laugh->SetVisibility(ESlateVisibility::Hidden);
	Monokuma_thread->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_normal->SetVisibility(ESlateVisibility::Hidden);
	Leon_normal->SetVisibility(ESlateVisibility::Hidden);

}
void UPlaygroundWidget::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UPlaygroundWidget::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}



