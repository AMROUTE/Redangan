#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"

// 采用Service Locator模式重构：集中管理“接口 → 实现”的注册与解析
struct FServiceContext
{
    FName LevelName;
    FString Mode; // e.g. "prod", "test"
};

class ServiceLocator
{
public:
    template<typename T>
    static void Register(T* Impl, const FName& Key = NAME_None)
    {
        const FName TypeName = GetTypeName<T>();
        FName UseKey = (Key == NAME_None) ? DefaultKey : Key;
        AutoMap().FindOrAdd(TypeName).Add(UseKey, reinterpret_cast<void*>(Impl));
    }

    template<typename T>
    static T* Resolve(const FServiceContext& Ctx)
    {
        const FName TypeName = GetTypeName<T>();
        if (auto* PerKey = AutoMap().Find(TypeName))
        {
            // 优先按 LevelName，其次按 Mode，最后默认
            if (void** Found = PerKey->Find(Ctx.LevelName))
                return reinterpret_cast<T*>(*Found);
            if (void** Found2 = PerKey->Find(FName(*Ctx.Mode)))
                return reinterpret_cast<T*>(*Found2);
            if (void** Found3 = PerKey->Find(DefaultKey))
                return reinterpret_cast<T*>(*Found3);
        }
        return nullptr;
    }

private:
    static TMap<FName, TMap<FName, void*>>& AutoMap()
    {
        static TMap<FName, TMap<FName, void*>> Registry;
        return Registry;
    }

    template<typename T>
    static FName GetTypeName()
    {
        // 简化：使用类名字符串作为键（演示用）
        return FName(typeid(T).name());
    }

    static const FName DefaultKey;
};
