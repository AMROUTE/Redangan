// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueWidgetBase.h"
#include "CanteenWidget.generated.h"

/**
 *
 */
UCLASS()
class DANGANRONPA_API UCanteenWidget : public UDialogueWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void InitializePortraits()override;
	virtual void OnBubbleClicked()override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_ThinkTalk;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Asahina_Worry;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Asahina_HeadLow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Asahina_IdleFrown;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Ishimaru_Think;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Monokuma_BigLaugh;
};
