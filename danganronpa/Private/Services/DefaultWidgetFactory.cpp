#include "Services/IWidgetFactory.h"
#include "HUD/DialogueWidget.h"
#include "HUD/PlaygroundWidget.h"
#include "HUD/InventoryWidget.h"
#include "HUD/BedroomAfterWidget.h"
#include "Blueprint/UserWidget.h"

// 采用Service Locator模式重构：默认UI工厂实现（示例，不要求可运行）
class FDefaultWidgetFactory : public IWidgetFactory
{
public:
    virtual UUserWidget* CreateDialogueWidget(APlayerController* PC) override
    {
        // 示例：真实项目应使用具体UClass/蓝图类
        return nullptr;
    }
    virtual UUserWidget* CreatePlaygroundWidget(APlayerController* PC) override { return nullptr; }
    virtual UUserWidget* CreateInventoryWidget(APlayerController* PC) override { return nullptr; }
    virtual UUserWidget* CreateBedroomWidget(APlayerController* PC) override { return nullptr; }
};

// 示例：注册默认实现（可由GameMode在BeginPlay时调用）
static void RegisterDefaultWidgetFactory()
{
    // ServiceLocator::Register<IWidgetFactory>(new FDefaultWidgetFactory());
}
