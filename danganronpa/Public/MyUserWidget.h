// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DANGANRONPA_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
    public:
	UPROPERTY(EditAnywhere, Category = "MyVariable")
	int32 IfWidgetEnd = 0;

	UFUNCTION(BlueprintCallable)
	int32 SetEnd(int32 variable);

};
