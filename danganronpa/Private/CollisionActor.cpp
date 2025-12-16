// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionActor.h"
#include <Kismet/GameplayStatics.h>
#include "MyCharacter.h"

// Sets default values
ACollisionActor::ACollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionActor::ChaDeath()
{
	ACharacter* Mycha = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyCharacter* MyCharacter = Cast<AMyCharacter> (Mycha);
	if (MyCharacter)
		MyCharacter->Death();
}

