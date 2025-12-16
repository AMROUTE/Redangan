// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"
#include "HUD/DTReader.h"
#include "InventoryWidget.generated.h"
class UButton;
class UTextBlock;
class UImage;
class UOverlay;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // 初始化函数
    virtual void NativeOnInitialized() override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
protected:
    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_Katana;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_Knife;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_Number;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_DrawerConter;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_Scratch;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_MaizonoHand;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_name1;

    UPROPERTY(meta = (BindWidget))
    UOverlay* Overlay_name2;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UDataTable> MyObject;

    UPROPERTY(meta = (BindWidget))
    UImage* table;

    UPROPERTY(meta = (BindWidget))
    UImage* Katana;

    UPROPERTY(meta = (BindWidget))
    UImage* DrawerConter;

    UPROPERTY(meta = (BindWidget))
    UImage* Scratch;

    UPROPERTY(meta = (BindWidget))
    UImage* MaizonoHand;

    UPROPERTY(meta = (BindWidget))
    UImage* Number;

    UPROPERTY(meta = (BindWidget))
    UImage* Knife;

    UPROPERTY(meta = (BindWidget))
    UImage* name1;

    UPROPERTY(meta = (BindWidget))
    UImage* name2;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_Katana;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_DrawerConter;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_scratch;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_MaizonoHand;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_Number;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_Knife;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_name1;

    UPROPERTY(meta = (BindWidget))
    UImage* unfind_name2;

    UPROPERTY(meta = (BindWidget))
    UImage* WhiteBackground;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Title;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DetailTitle;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Details;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Close;

    // 绑定控件：关闭按钮
    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    // 添加CloseButton的点击事件
    UFUNCTION()
    void OnCloseButtonClicked();

    /*UFUNCTION()
    void OnOverlayMouseEnter(UOverlay* HoveredOverlay);

    UFUNCTION()
    void OnOverlayMouseLeave(UOverlay* HoveredOverlay);*/

    UOverlay* HoveredOverlay;
    void PopulateInventory();
    void BindOverlaysFromDataTable();
    void ShowDetails(UOverlay* HoveredOverlayLocal);
    void HideDetails();
    UOverlay* FindOverlayByName(FName OverlayName) const;
    UOverlay* GetHoveredOverlay(const FPointerEvent& InMouseEvent) const;

private:
    TArray<FObjects*> Objects;
    TMap<UOverlay*, FString> OverlayDescriptions;
    TMap<UOverlay*, FString> OverlayTitles;
};
