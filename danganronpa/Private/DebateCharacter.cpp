#include "DebateCharacter.h"

// 构造函数
ADebateCharacter::ADebateCharacter()
{
    // 设定每帧更新
    PrimaryActorTick.bCanEverTick = true;
}

// BeginPlay() 在游戏开始时调用
void ADebateCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// 每帧调用 Tick()
void ADebateCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}




