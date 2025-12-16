#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Engine/DataTable.h"
#include"Components/Image.h"
#include "DTReader.generated.h"
USTRUCT(BlueprintType)
struct FDialogData : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 对话内容
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString DialogueText;

	// 可选：对话角色（如果有）
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	bool intro;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	bool out;
};
USTRUCT(BlueprintType)
struct FKototama : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	FText Name;

	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	TObjectPtr<UTexture2D>Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	bool Get;

};
USTRUCT(BlueprintType)
struct FObjects : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 物品的名称
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FString ObjectName;

	// 物品的详细描述
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FString ObjectDetail;

	// 是否已获取
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	bool bIsAcquired;

	// 物品的图片引用（使用纹理）
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FSoftObjectPath ObjectImage;
};
UCLASS()
class DANGANRONPA_API ADTReader : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ADTReader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* MyDialogue;//*******重要：用于在BP内添加一个DataTable


	TArray<FDialogData*>DialogueData;
};