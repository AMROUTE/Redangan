#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "Engine/DataTable.h"
#include "MyCharacter.generated.h"


class UUserWidget;
class AdanganronpaProjectile;
class UCameraComponent;


UCLASS()
class DANGANRONPA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Death")
	void Death();

	UPROPERTY(EditAnywhere, Category = "Projectile")
	USceneComponent* SpawnProjectileScene;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	bool bCurrentProjectileIsRight = true;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AdanganronpaProjectile> DanGanProjectile;


	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FireProjectile();

	FRotator CalculateSpawnRotation();

	// 函数：启动旋转循环
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StartCameraRotationCycle();

	// 函数：停止旋转循环
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StopCameraRotationCycle();

	// 函数：更改目标旋转角度
	UFUNCTION(BlueprintCallable)
	void ChangeCameraRotation();

	// 函数：平滑旋转摄像机
	UFUNCTION(BlueprintCallable)
	void SmoothCameraRotation(float DeltaTime);

	// 定时器句柄
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FTimerHandle RotationTimerHandle;

	// 当前旋转角度的索引
	UPROPERTY(EditAnywhere, Category = "Rotation")
	int32 CurrentRotationIndex;

	// 旋转角度数组
	UPROPERTY(EditAnywhere, Category = "Rotation")
	TArray<float> RotationAngles;

	// 累计时间
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Rotation")
	float RotationTimeElapsed;

	// 最大旋转时间
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float MaxRotationTime;

	// tick死亡调用检测
	UPROPERTY(EditAnywhere, Category = "Death")
	int32 ifDeath=0;

	// 检查是否达到最大旋转时间
	UFUNCTION(BlueprintCallable)
	void CheckDeathCondition();

	// 摄像机和SpringArm组件的引用，需由蓝图提供
	UPROPERTY(EditAnywhere,  Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,  Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	/*UFUNCTION(BlueprintCallable, Category = "TalkingSystem")
	void OnInitLoadingWidget();

	UPROPERTY(EditAnywhere, Category = "TalkingSystem")
	TSubclassOf<UUserWidget> TalkingWidgetClass;

	UPROPERTY(EditAnywhere, Category = "TalkingSystem")
	UDataTable* TalkingDataTable;

	UPROPERTY()
	TObjectPtr <UUserWidget> CreatedTalkingWidget;*/

};

