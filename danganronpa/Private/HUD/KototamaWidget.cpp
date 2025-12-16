// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/KototamaWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>

/*void UKototamaWidget::SetImage(UTexture2D* NewTexture)
{
    // 创建 Slate Brush 并设置贴图
    FSlateBrush Brush;
    Brush.SetResourceObject(NewTexture);
    KototamaImage->SetBrush(Brush);

}*/
void UKototamaWidget::SetImage(UTexture2D* NewTexture)
{
    if (!KototamaImage)
    {
        UE_LOG(LogTemp, Error, TEXT("KototamaImage is not initialized!"));
        return;
    }

    if (!NewTexture)
    {
        UE_LOG(LogTemp, Error, TEXT("NewTexture is invalid!"));
        return;
    }

    // 创建 Slate Brush 并设置贴图
    FSlateBrush Brush;
    Brush.ImageSize = FVector2D(NewTexture->GetSizeX(), NewTexture->GetSizeY());
    Brush.SetResourceObject(NewTexture);
    KototamaImage->SetBrush(Brush);

    // 确保控件可见
    KototamaImage->SetVisibility(ESlateVisibility::Visible);

    UE_LOG(LogTemp, Log, TEXT("Successfully set image!"));
}


void UKototamaWidget::SetName(const FText& NewText)
{
    if (KototamaName)
    {
        KototamaName->SetText(NewText);
    }
}

void UKototamaWidget::SetDescription(const FText& NewText)
{
    if (KototamaDescription)
    {
        KototamaDescription->SetText(NewText);
    }
}

