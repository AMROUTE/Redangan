#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KototamaWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UKototamaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KototamaName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KototamaDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> KototamaImage;

	// 设置图像的方法
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetImage(UTexture2D* NewTexture);

	// 设置文本的方法
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetName(const FText& NewText);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetDescription(const FText& NewText);
};
