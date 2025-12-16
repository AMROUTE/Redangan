#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DebateCharacter.generated.h"


UCLASS()
class DANGANRONPA_API ADebateCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // 构造函数
    ADebateCharacter();

protected:
    // 游戏开始时或对象被重置时调用
    virtual void BeginPlay() override;

public:
    // 每帧更新时调用
    virtual void Tick(float DeltaTime) override;
};
