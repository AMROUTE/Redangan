#include "MyCharacter.h"
#include "../danganronpaProjectile.h"
#include "Blueprint/UserWidget.h"

#include "DialoguePlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>



// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnProjectileScene = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProjectileScene"));
	SpawnProjectileScene->SetupAttachment(RootComponent);

	// 初始化
	CurrentRotationIndex = 0;
	RotationAngles = { 120.f, 300.f, 250.f, 0.f, 60.f };  // 旋转角度顺序
	RotationTimeElapsed = 0.f;
	MaxRotationTime = 60.f;  // 设置最大旋转时间为 300 秒


	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Death();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// 设置为游戏模式输入
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		// 确保显示鼠标光标
		PlayerController->bShowMouseCursor = true;
	}

	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotationTimeElapsed += DeltaTime;
	
	// 处理摄像机平滑旋转
	SmoothCameraRotation(DeltaTime);

	// 检查死亡条件
	CheckDeathCondition();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartCameraRotationCycle);


}

void AMyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	ADialoguePlayerController* PlayerController = Cast<ADialoguePlayerController>(GetController());
	if (PlayerController != nullptr)
	{

		PlayerController->ShowRestartWidget();
	}
}

void AMyCharacter::FireProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("FireProjectile"));

	// 获取玩家控制器
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector SpawnLocation = FVector::ZeroVector;  // 初始化 SpawnLocation

	if (PlayerController)
	{
		// 屏幕坐标 (0, 0) 为左下角
		FVector2D ScreenPosition(0.f, 0.f); // 屏幕左下角的坐标

		// 将屏幕坐标转换为世界坐标
		FVector WorldLocation, WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPosition, WorldLocation, WorldDirection);

		// 使用转换后的世界坐标作为射出位置
		SpawnLocation = WorldLocation;
	}

	FRotator SpawnRotation = CalculateSpawnRotation();

	// 设置 Spawn Parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;  // 设置所有者，通常为当前 Actor
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AdanganronpaProjectile>
		(DanGanProjectile, SpawnLocation, SpawnRotation, SpawnParams);

}

FRotator AMyCharacter::CalculateSpawnRotation()
{
	FVector StartLocation = SpawnProjectileScene->GetComponentLocation();

	FVector Endlocation = { 0,0,0 };
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);

		// 将屏幕坐标转换为世界坐标
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;

		UGameplayStatics::DeprojectScreenToWorld(PlayerController, FVector2D(MouseX, MouseY),
			MouseWorldLocation, MouseWorldDirection);

		FVector LineTraceEnd = MouseWorldLocation + (MouseWorldDirection * 80000.0f);

		FHitResult HItResult;

		TArray<AActor*> ActorsToIgnore;

		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(), StartLocation, LineTraceEnd,
			ETraceTypeQuery::TraceTypeQuery1,
			false, ActorsToIgnore,
			EDrawDebugTrace::None,  // 不绘制射线
			HItResult,
			true
		);


		if (bHit)
		{
			Endlocation = HItResult.ImpactPoint;
		}
		else
		{
			Endlocation = HItResult.TraceEnd;
		}
		// 打印 FVector 的值，ToString() 会返回 "X=0.000000 Y=0.000000 Z=0.000000"
		UE_LOG(LogTemp, Warning, TEXT("EndLocation: %s"), *Endlocation.ToString());
	}

	FVector StartLoc = SpawnProjectileScene->GetComponentLocation();

	FRotator ReturnValue = UKismetMathLibrary::FindLookAtRotation(StartLoc, Endlocation);
	// 打印 FVector 的值


	return ReturnValue;

}


void AMyCharacter::StartCameraRotationCycle()
{
	// 启动每3秒切换旋转角度的定时器
	GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, this, &AMyCharacter::ChangeCameraRotation, 2.0f, true);
}

void AMyCharacter::StopCameraRotationCycle()
{
	// 停止旋转循环
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
}

void AMyCharacter::ChangeCameraRotation()
{
	// 获取下一个目标旋转角度
	if (RotationAngles.Num() > 0)
	{
		// 循环访问旋转角度
		CurrentRotationIndex = (CurrentRotationIndex + 1) % RotationAngles.Num();
		float TargetYaw = RotationAngles[CurrentRotationIndex];

		// 获取当前摄像机的旋转
		if (CameraComponent)
		{
			FRotator CurrentRotation = CameraComponent->GetComponentRotation();

			// 创建一个目标旋转，只改变Yaw角度
			FRotator TargetRotation = CurrentRotation;
			TargetRotation.Yaw = TargetYaw;

			

			// 使用 SetControlRotation 来更新控制器的旋转
			Controller->SetControlRotation(TargetRotation);
		}
	}
}


void AMyCharacter::SmoothCameraRotation(float DeltaTime)
{
	// 每帧平滑过渡旋转（如果摄像机和SpringArm存在）
	if (CameraComponent && SpringArmComponent)
	{
		FRotator CurrentRotation = CameraComponent->GetComponentRotation();
		FRotator TargetRotation = CameraComponent->GetComponentRotation();

		// 使用 FInterpTo 来平滑过渡旋转
		FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
		CameraComponent->SetWorldRotation(SmoothedRotation);
	}
}

void AMyCharacter::CheckDeathCondition()
{
	if (!ifDeath)
	{
		// 累加旋转时间
		RotationTimeElapsed += GetWorld()->GetDeltaSeconds();

		// 如果累计时间超过300秒，调用死亡函数
		if (RotationTimeElapsed >= MaxRotationTime)
		{
			Death();  // 假设你有 Death() 函数在 Character 中
			ifDeath++;
		}
	}
	
	
}

