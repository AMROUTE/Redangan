#pragma once

#include "CoreMinimal.h"

// 采用Service Locator模式重构：定义对话数据仓库接口
class IDialogueRepository
{
public:
    virtual ~IDialogueRepository() = default;
    virtual bool GetNextDialogue(FString& OutCharacterName, FString& OutDialogueText, UTexture2D*& OutCharacterImage) = 0;
    virtual void Reset() = 0;
};
