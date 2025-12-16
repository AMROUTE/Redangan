#include "DialoguePlayerController.h"
#include"HUD/RestartWidget.h"


void ADialoguePlayerController::ShowRestartWidget()
{
	if (RestartWidgetClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Daaa"));

		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, RestartWidgetClass);
		RestartWidget->AddToViewport();

	}

}
void ADialoguePlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

