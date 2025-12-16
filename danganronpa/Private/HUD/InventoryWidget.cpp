// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Blueprint/WidgetTree.h"

void UInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    FName _rowname = FName(TEXT("1"));
    FString ContextString = TEXT("TEST");
    // 关闭按钮绑定点击事件
    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseButtonClicked);
    }
    FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/resources/datatable/DTRenew/DT_ky_Object.DT_ky_Object'");
    MyObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
    if (MyObject)
    {
        MyObject->GetAllRows(ContextString, Objects);
    }
    DetailTitle->SetVisibility(ESlateVisibility::Collapsed);
    Details->SetVisibility(ESlateVisibility::Collapsed);
    WhiteBackground->SetVisibility(ESlateVisibility::Collapsed);
    PopulateInventory();
    BindOverlaysFromDataTable();
    // 依此类推，检查所有图片控件
}

void UInventoryWidget::PopulateInventory()
{
    TArray<FName> RowNames = MyObject->GetRowNames();
    for (int32 Index = 0; Index < Objects.Num(); ++Index)
    {
        FName RowName = RowNames[Index];
        FString ImageName = RowName.ToString();
        FString reImageName = TEXT("unfind_") + ImageName;
        FString OverlayName = TEXT("overlay_") + ImageName;
        UImage* MyImage = Cast<UImage>(WidgetTree->FindWidget(*ImageName));
        UImage* reMyImage = Cast<UImage>(WidgetTree->FindWidget(*reImageName));
        UOverlay* MyOverlay = Cast<UOverlay>(WidgetTree->FindWidget(*OverlayName));
        if (Objects[Index]->bIsAcquired)
        {
            MyImage->SetVisibility(ESlateVisibility::Visible);
            reMyImage->SetVisibility(ESlateVisibility::Collapsed);
            MyOverlay->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            MyImage->SetVisibility(ESlateVisibility::Collapsed);
            reMyImage->SetVisibility(ESlateVisibility::Visible);
            MyOverlay->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

}

void UInventoryWidget::BindOverlaysFromDataTable()
{
    if (!MyObject) return; // 确保数据表存在

    // 获取数据表中的所有行
    const FString ContextString(TEXT("Inventory Data Table Context"));
    TArray<FName> RowNames = MyObject->GetRowNames();

    for (TArray<FName>::TConstIterator It = RowNames.CreateConstIterator(); It; ++It)
    {
        const FName& RowName = *It;

        // 获取数据表中的一行
        FObjects* RowData = MyObject->FindRow<FObjects>(RowName, ContextString, true);
        if (!RowData) continue;

        // 根据 OverlayName 动态找到对应的 Overlay
        UOverlay* Overlay = FindOverlayByName(RowName);
        if (!Overlay) continue;

        // 保存 Overlay 和描述文本到映射表中
        OverlayDescriptions.Add(Overlay, RowData->ObjectDetail);
        OverlayTitles.Add(Overlay, RowData->ObjectName);
    }

}
UOverlay* UInventoryWidget::FindOverlayByName(FName OverlayName) const
{
    // 在当前 WidgetTree 中查找 Overlay
    FString Overlay = TEXT("overlay_") + OverlayName.ToString();
    return Cast<UOverlay>(WidgetTree->FindWidget(*Overlay));
}

UOverlay* UInventoryWidget::GetHoveredOverlay(const FPointerEvent& InMouseEvent) const
{
    for (const auto& OverlayPair : OverlayDescriptions)
    {
        UOverlay* Overlay = OverlayPair.Key;
        if (!Overlay) continue;

        // 检测鼠标是否悬停在当前 Overlay 上
        FGeometry OverlayGeometry = Overlay->GetCachedGeometry();
        if (OverlayGeometry.IsUnderLocation(InMouseEvent.GetScreenSpacePosition()))
        {
            return Overlay;
        }
    }
    return nullptr; // 没有找到悬停的 Overlay
}




void UInventoryWidget::OnCloseButtonClicked()
{
    // 执行关闭逻辑：移除UI
    RemoveFromParent();

    UE_LOG(LogTemp, Warning, TEXT("关闭按钮被点击"));
}
void UInventoryWidget::ShowDetails(UOverlay* HoveredOverlayLocal)
{
    if (!HoveredOverlayLocal || !DetailTitle || !Details) return;

    FString* DetailsText = OverlayDescriptions.Find(HoveredOverlayLocal);
    FString* DetailTitleText = OverlayTitles.Find(HoveredOverlayLocal);

    if (DetailsText && DetailTitleText)
    {
        Details->SetText(FText::FromString(*DetailsText));
        DetailTitle->SetText(FText::FromString(*DetailTitleText));
        DetailTitle->SetVisibility(ESlateVisibility::Visible);
        Details->SetVisibility(ESlateVisibility::Visible);
        WhiteBackground->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInventoryWidget::HideDetails()
{
    if (!DetailTitle || !Details) return;

    DetailTitle->SetVisibility(ESlateVisibility::Collapsed);
    Details->SetVisibility(ESlateVisibility::Collapsed);
    WhiteBackground->SetVisibility(ESlateVisibility::Collapsed);
}

FReply UInventoryWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    UOverlay* AHoveredOverlay = GetHoveredOverlay(InMouseEvent);
    if (AHoveredOverlay)
    {
        ShowDetails(AHoveredOverlay); // 显示详情
    }
    else
    {
        HideDetails(); // 隐藏详情
    }
    return FReply::Unhandled();
}

