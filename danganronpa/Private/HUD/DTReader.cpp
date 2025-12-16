#include "HUD/DTReader.h"

// Sets default values
ADTReader::ADTReader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADTReader::BeginPlay()
{
	Super::BeginPlay();

	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");

	if (MyDialogue)
	{
		TArray<FDialogData*>Dialogues;
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues已获取DataTable所有行信息
		DialogueData = Dialogues;
		/*for (auto _data : Dialogues) {

		}*/
		FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false代表不报错
	}
}

// Called every frame
void ADTReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

