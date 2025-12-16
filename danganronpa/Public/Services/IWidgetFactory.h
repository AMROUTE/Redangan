#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// 采用Service Locator模式重构：定义UI工厂接口，调用方只依赖接口
class IWidgetFactory
{
public:
    virtual ~IWidgetFactory() = default;
    virtual UUserWidget* CreateDialogueWidget(APlayerController* PC) = 0;
    virtual UUserWidget* CreatePlaygroundWidget(APlayerController* PC) = 0;
    virtual UUserWidget* CreateInventoryWidget(APlayerController* PC) = 0;
    virtual UUserWidget* CreateBedroomWidget(APlayerController* PC) = 0;
};
