#include "Player/NaegiController.h"
#include <HUD/BedroomAfterWidget.h>
#include <HUD/KototamaWidget.h>
#include "TimerManager.h"
#include <HUD/DTReader.h>
#include "Kismet/GameplayStatics.h"
#include <HUD/DialogueWidget.h>
#include <HUD/PlaygroundWidget.h>
#include <HUD/InventoryWidget.h>
#include <HUD/WidgetBuilder.h>
#include <Services/ServiceLocator.h>
#include <Services/IWidgetFactory.h>
// 采用Builder模式重构：通过统一的Builder/Director创建并初始化关卡UI
void ANaegiController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	KototamaWidget = CreateWidget<UKototamaWidget>(this, KototamaWidgetClass);
	CreateDialogueWidget();
}

void ANaegiController::CreateDialogueWidget()
{
	// 采用Builder模式重构：避免控制器内多分支的CreateWidget与初始化细节
	const FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(this);
	FWidgetBuildDirector Director(GetWorld(), this);

	// 使用按关卡选择的 Builder 构建并返回结果
	extern UUserWidget* BuildLevelWidget(UWorld* World, APlayerController* PC);
	UUserWidget* BuiltWidget = BuildLevelWidget(GetWorld(), this);

	// 采用Service Locator模式重构：示例通过定位器解析UI工厂（逻辑演示）
	FServiceContext Ctx{ CurrentLevel, TEXT("prod") };
	IWidgetFactory* Factory = ServiceLocator::Resolve<IWidgetFactory>(Ctx);
	// 注意：此处仅演示接口解析，不要求实际调用

	// 保存到具体成员（演示：根据类型尝试赋值）
	if (UDialogueWidget* AsDialogue = Cast<UDialogueWidget>(BuiltWidget))
	{
		DialogueWidget = AsDialogue;
		UE_LOG(LogTemp, Log, TEXT("DialogueWidget Built by Builder"));
	}
	else if (UPlaygroundWidget* AsPlayground = Cast<UPlaygroundWidget>(BuiltWidget))
	{
		PlaygroundWidget = AsPlayground;
		UE_LOG(LogTemp, Log, TEXT("PlaygroundWidget Built by Builder"));
	}
	else if (UInventoryWidget* AsInventory = Cast<UInventoryWidget>(BuiltWidget))
	{
		InventoryWidget = AsInventory;
		UE_LOG(LogTemp, Log, TEXT("InventoryWidget Built by Builder"));
	}
	else if (UBedroomAfterWidget* AsBedroom = Cast<UBedroomAfterWidget>(BuiltWidget))
	{
		BedroomAfterWidget = AsBedroom;
		UE_LOG(LogTemp, Log, TEXT("BedroomAfterWidget Built by Builder"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching widget built for level: %s"), *CurrentLevel.ToString());
	}
}


void ANaegiController::GetKototama(FKototama* Kototama)
{
	KototamaWidget->SetName(Kototama->Name);
	KototamaWidget->SetDescription(Kototama->Description);
	KototamaWidget->SetImage((Kototama->Image));
	KototamaWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]()
		{
			if (KototamaWidget)
			{
				KototamaWidget->RemoveFromParent();
			}
		}), 3.0f, false);

}

