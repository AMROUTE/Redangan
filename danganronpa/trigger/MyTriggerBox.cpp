#include "MyTriggerBox.h"
#include "../Public/MyCharacter.h"
#include "../danganronpaProjectile.h"  // 包含子弹类头文件
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// 构造函数
AMyTriggerBox::AMyTriggerBox()
{
    // 初始化触发框
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    // 设置触发框碰撞属性
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
}

// 当重叠发生时的回调函数
void AMyTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(AdanganronpaProjectile::StaticClass())) // 判断是否为子弹
    {
        UE_LOG(LogTemp, Warning, TEXT("子弹与触发框发生碰撞"));

        // 执行相应的触发事件
        OnTriggerHit();  // 执行触发框事件
    }
}

// 根据触发框执行不同的逻辑
void AMyTriggerBox::OnTriggerHit()
{
    // 你可以根据触发框的名称或其他属性执行不同的逻辑
    if (this->GetName() == TEXT("triggerFalse"))
    {
        UE_LOG(LogTemp, Warning, TEXT("False 被触发"));
        TriggerDeath();
        // 触发框1的逻辑
    }
    else if (this->GetName() == TEXT("triggerRight"))
    {
        // 执行打开下一个关卡的操作
        UGameplayStatics::OpenLevel(this, FName("dialogueEndStage"));

        UE_LOG(LogTemp, Warning, TEXT("Right 被触发"));
        // 触发框2的逻辑
    }
}

void AMyTriggerBox::TriggerDeath()
{
    // 获取当前玩家控制器
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        // 获取当前玩家控制的角色
        AMyCharacter* MyCharacter = Cast<AMyCharacter>(PlayerController->GetPawn());

        // 如果成功转换为 MyCharacter，调用其死亡函数
        if (MyCharacter)
        {
            MyCharacter->Death(); // 调用死亡函数
        }
    }
}

void AMyTriggerBox::OpenNextLevel()
{
    // 加载 Dialogue2 关卡
    UGameplayStatics::OpenLevel(this, TEXT("Dialogue2"));
}


