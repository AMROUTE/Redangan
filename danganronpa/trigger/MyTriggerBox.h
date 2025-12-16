#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"




UCLASS()
class DANGANRONPA_API AMyTriggerBox : public ATriggerBox
{

    GENERATED_BODY()

public:
    // 构造函数
    AMyTriggerBox();

protected:
    // 触发框
    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    UBoxComponent* TriggerBox;

    // 重叠事件函数
    UFUNCTION(BlueprintCallable)
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

public:
    // 被触发时执行的事件
    UFUNCTION(BlueprintCallable)
    void OnTriggerHit();

    UFUNCTION(BlueprintCallable)
    void TriggerDeath();

    UFUNCTION(BlueprintCallable)
    void OpenNextLevel();
};

