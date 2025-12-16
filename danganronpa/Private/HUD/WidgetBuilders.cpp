#include "HUD/WidgetBuilder.h"
#include "Player/NaegiController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HUD/DialogueWidget.h"
#include "HUD/PlaygroundWidget.h"
#include "HUD/InventoryWidget.h"
#include "HUD/BedroomAfterWidget.h"

// 采用Builder模式重构：针对不同关卡的Widget由各具体Builder负责创建与初始化
namespace WidgetBuilders
{
    // 抽象基类的一个通用实现骨架（可复用步骤）
    // 采用Builder模式重构：BaseBuilder复用通用构建步骤
    class FBaseWidgetBuilder : public IWidgetBuilder
    {
    public:
        virtual void Reset(UWorld* InWorld, APlayerController* InPC) override
        {
            World = InWorld;
            PC = InPC;
            Result = nullptr;
        }

        virtual void CreateRoot() override {}

        virtual void ConfigureInput() override {}

        virtual void BuildHierarchy() override {}

        virtual void AddToViewport() override
        {
            if (Result)
            {
                Result->AddToViewport();
            }
        }

        virtual UUserWidget* GetResult() const override { return Result; }

    protected:
        UWorld* World{ nullptr };
        APlayerController* PC{ nullptr };
        UUserWidget* Result{ nullptr };
    };

    // 各关卡的具体 Builder
    // 采用Builder模式重构：课堂关卡Widget的具体Builder
    class FClassroomDialogueBuilder : public FBaseWidgetBuilder
    {
    public:
        FName WidgetClassPath{ TEXT("/Game/UI/WBP_Dialogue") }; // 示例路径，逻辑演示
        virtual void CreateRoot() override
        {
            ANaegiController* NC = Cast<ANaegiController>(PC);
            if (NC)
            {
                Result = CreateWidget<UDialogueWidget>(PC, NC->DialogueWidgetClass);
            }
        }
        virtual void ConfigureInput() override
        {
            if (PC)
            {
                PC->SetInputMode(FInputModeUIOnly());
                PC->bShowMouseCursor = true;
            }
        }
    };

    // 采用Builder模式重构：操场关卡Widget的具体Builder
    class FPlaygroundBuilder : public FBaseWidgetBuilder
    {
    public:
        virtual void CreateRoot() override
        {
            ANaegiController* NC = Cast<ANaegiController>(PC);
            if (NC)
            {
                Result = CreateWidget<UPlaygroundWidget>(PC, NC->PlaygroundWidgetClass);
            }
        }
        virtual void ConfigureInput() override
        {
            if (PC)
            {
                PC->SetInputMode(FInputModeGameAndUI());
                PC->bShowMouseCursor = true;
            }
        }
    };

    // 采用Builder模式重构：背包关卡Widget的具体Builder
    class FInventoryBuilder : public FBaseWidgetBuilder
    {
    public:
        virtual void CreateRoot() override
        {
            ANaegiController* NC = Cast<ANaegiController>(PC);
            if (NC)
            {
                Result = CreateWidget<UInventoryWidget>(PC, NC->InventoryWidgetClass);
            }
        }
        virtual void ConfigureInput() override
        {
            if (PC)
            {
                PC->SetInputMode(FInputModeUIOnly());
                PC->bShowMouseCursor = true;
            }
        }
    };

    // 采用Builder模式重构：卧室剧情Widget的具体Builder
    class FBedroomAfterBuilder : public FBaseWidgetBuilder
    {
    public:
        virtual void CreateRoot() override
        {
            ANaegiController* NC = Cast<ANaegiController>(PC);
            if (NC && NC->BedroomAfterWidgetClass)
            {
                Result = CreateWidget<UBedroomAfterWidget>(PC, NC->BedroomAfterWidgetClass);
            }
        }
        virtual void ConfigureInput() override
        {
            if (PC)
            {
                PC->SetInputMode(FInputModeUIOnly());
                PC->bShowMouseCursor = true;
            }
        }
    };
}

// 一个选择器函数（示例）供控制器选择具体 Builder
// 采用Builder模式重构：根据关卡选择具体Builder的工厂/选择器
static TUniquePtr<IWidgetBuilder> SelectBuilderByLevel(FName LevelName)
{
    using namespace WidgetBuilders;
    if (LevelName == FName("Map_Classroom"))
    {
        return MakeUnique<FClassroomDialogueBuilder>();
    }
    else if (LevelName == FName("Map_Playground"))
    {
        return MakeUnique<FPlaygroundBuilder>();
    }
    else if (LevelName == FName("TestLevel"))
    {
        return MakeUnique<FInventoryBuilder>();
    }
    else if (LevelName == FName("Map_BedroomAfter1"))
    {
        return MakeUnique<FBedroomAfterBuilder>();
    }
    return MakeUnique<FBaseWidgetBuilder>();
}

// 供外部使用的统一入口
// 采用Builder模式重构：统一入口由Director按步骤完成构建
UUserWidget* BuildLevelWidget(UWorld* World, APlayerController* PC)
{
    const FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(World);
    auto Builder = SelectBuilderByLevel(CurrentLevel);
    FWidgetBuildDirector Director(World, PC);
    return Director.Construct(*Builder.Get());
}
