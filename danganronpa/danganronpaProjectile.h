#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "danganronpaProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config = Game)
class AdanganronpaProjectile : public AActor
{
    GENERATED_BODY()

    /** Sphere collision component */
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    USphereComponent* CollisionComp;

    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovement;

    /** Static mesh component for the projectile visual */
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* MeshComp;

public:
    AdanganronpaProjectile();

    /** called when projectile hits something */
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    /** Returns CollisionComp subobject **/
    USphereComponent* GetCollisionComp() const { return CollisionComp; }
    /** Returns ProjectileMovement subobject **/
    UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
