// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RestartWidget.h"
#include "Components/Button.h"
#include "DialoguePlayerController.h"
#include "Kismet/GameplayStatics.h"

void URestartWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();
	if (RestartButton != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Daaa"));
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}
	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
	}
}

void URestartWidget::OnRestartClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("ป๎มห"));
	ADialoguePlayerController* PlayerController=Cast<ADialoguePlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}
void URestartWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}