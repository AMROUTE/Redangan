// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"
#include "Services/ServiceLocator.h"
#include "Services/IDialogueRepository.h"
#include "Events/EventBus.h"


// 采用Service Locator模式重构：通过仓库接口获取下一条对话（示例，逻辑演示）
bool ADialogueManager::GetNextDialogue(FString& OutCharacterName, FString& OutDialogueText, UTexture2D*& OutCharacterImage)
{
    FServiceContext Ctx{ *UGameplayStatics::GetCurrentLevelName(this), TEXT("prod") };
    IDialogueRepository* Repo = ServiceLocator::Resolve<IDialogueRepository>(Ctx);
    if (Repo)
    {
        return Repo->GetNextDialogue(OutCharacterName, OutDialogueText, OutCharacterImage);
    }
    // 回退：保留原逻辑（可选）
    if (!DialogueTable) return false;
    static const FString ContextString(TEXT("Dialogue Context"));
    TArray<FName> RowNames = DialogueTable->GetRowNames();
    if (CurrentIndex >= RowNames.Num()) { return false; }
    FName CurrentRowName = RowNames[CurrentIndex];
    FDialogueRow* CurrentRow = DialogueTable->FindRow<FDialogueRow>(CurrentRowName, ContextString);
    if (CurrentRow)
    {
        OutCharacterName = CurrentRow->CharacterName;
        OutDialogueText = CurrentRow->DialogueText;
        OutCharacterImage = CurrentRow->CharacterImage;
        CurrentIndex++;
        return true;
    }
    return false;
}
    return false;
}


// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADialogueManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

