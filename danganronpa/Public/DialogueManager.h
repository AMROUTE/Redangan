// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/DataTable.h" // 包含 DataTable 支持
#include "UObject/NoExportTypes.h"
#include "DialogueManager.generated.h"

// 定义对话表的行结构
USTRUCT(BlueprintType)
struct FDialogueRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString CharacterName; // 角色名字

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString DialogueText; // 对话内容

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UTexture2D* CharacterImage; // 角色立绘
};



UCLASS()
class DANGANRONPA_API ADialogueManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADialogueManager();

    // 当前对话表
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueTable;

    // 当前对话索引
    UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
    int32 CurrentIndex = 0;

    // 获取当前对话
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool GetNextDialogue(FString& OutCharacterName, FString& OutDialogueText, UTexture2D*& OutCharacterImage);

   


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
