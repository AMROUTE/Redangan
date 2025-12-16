#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BloodActor.generated.h"

UCLASS()
class DANGANRONPA_API ABloodActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABloodActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** 3D Text render component to display the text */
	UPROPERTY(VisibleAnywhere, Category = "Text")
	UTextRenderComponent* TextComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovement;
};
