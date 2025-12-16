
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DialoguePlayerController.generated.h"


class URestartWidget;

/**
 *
 */
UCLASS()
class DANGANRONPA_API ADialoguePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<URestartWidget>RestartWidgetClass;

	void ShowRestartWidget();
	void HideRestartWidget();
private:
	UPROPERTY()
	TObjectPtr <URestartWidget>RestartWidget;

};
