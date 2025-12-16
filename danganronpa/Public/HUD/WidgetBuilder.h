#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// 采用Builder模式重构：Builder接口定义分步骤创建并初始化Widget
class IWidgetBuilder
{
public:
    virtual ~IWidgetBuilder() = default;

    virtual void Reset(UWorld* InWorld, APlayerController* InPC) = 0;
    virtual void CreateRoot() = 0;
    virtual void ConfigureInput() = 0;
    virtual void BuildHierarchy() = 0;
    virtual void AddToViewport() = 0;
    virtual UUserWidget* GetResult() const = 0;
};

// 采用Builder模式重构：Director负责按统一流程驱动具体Builder
class FWidgetBuildDirector
{
public:
    FWidgetBuildDirector(UWorld* InWorld, APlayerController* InPC)
        : World(InWorld), PC(InPC) {}

    // 传入具体 Builder 执行统一构建流程
    UUserWidget* Construct(IWidgetBuilder& Builder)
    {
        Builder.Reset(World, PC);
        Builder.CreateRoot();
        Builder.ConfigureInput();
        Builder.BuildHierarchy();
        Builder.AddToViewport();
        return Builder.GetResult();
    }

private:
    UWorld* World{ nullptr };
    APlayerController* PC{ nullptr };
};
