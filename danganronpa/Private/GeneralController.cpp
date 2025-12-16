#include "GeneralController.h"
#include <DialogueWidgetBase.h>
#include <HUD/KototamaWidget.h>
#include "TimerManager.h"
#include <HUD/DTReader.h>
void AGeneralController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	KototamaWidget = CreateWidget<UKototamaWidget>(this, KototamaWidgetClass);
	CreateDialogueWidget();
}
void AGeneralController::CreateDialogueWidget()
{
	if (DialogueWidgetClass != nullptr)
	{
		//SetPause(true);
		SetInputMode(FInputModeUIOnly());//仅支持UI输入

		bShowMouseCursor = true;
		DialogueWidget = CreateWidget<UDialogueWidgetBase>(this, DialogueWidgetClass);

		if (DialogueWidget) {
			DialogueWidget->AddToViewport();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Subclass Fail"));
		}


	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Class"));
	}
}

void AGeneralController::GetKototama(FKototama* Kototama)
{
	KototamaWidget->SetName(Kototama->Name);
	KototamaWidget->SetDescription(Kototama->Description);
	KototamaWidget->SetImage((Kototama->Image));
	KototamaWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]()
		{
			if (KototamaWidget)
			{
				KototamaWidget->RemoveFromParent();
			}
		}), 3.0f, false);
}


