#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeneralController.generated.h"
class UDialogueWidgetBase;
class UKototamaWidget;
struct FKototama;
/**
 *
 */
UCLASS()
class DANGANRONPA_API AGeneralController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDialogueWidgetBase>DialogueWidgetClass;

	UPROPERTY()
	TObjectPtr<UKototamaWidget>KototamaWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UKototamaWidget>KototamaWidgetClass;

	void CreateDialogueWidget();

	UPROPERTY()
	TObjectPtr<UDialogueWidgetBase>DialogueWidget;

	void GetKototama(FKototama* Kototama);
	/*FSlateBrush DefaultBrush;
	DefaultBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Idle")));

	FSlateBrush HoverBrush;
	HoverBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Focus")));*/
private:
	FTimerHandle TimerHandle1;
};

