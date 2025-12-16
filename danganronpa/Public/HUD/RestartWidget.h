#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"


class UButton;
/**
 *
 */
UCLASS(Blueprintable)
class DANGANRONPA_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	TObjectPtr<UButton> ExitButton;

	UFUNCTION(BlueprintCallable)
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void OnRestartClicked();
	UFUNCTION(BlueprintCallable)
	void OnExitClicked();
};
