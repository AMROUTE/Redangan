#include "danganronpaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "trigger/MyTriggerBox.h"

AdanganronpaProjectile::AdanganronpaProjectile()
{
    // Use a sphere as a simple collision representation
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->SetGenerateOverlapEvents(true); // Enable overlap events
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AdanganronpaProjectile::OnHit); // Set up a notification for when this component hits something blocking

    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Set as root component
    RootComponent = CollisionComp;

    // Add a static mesh for the projectile visual
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(CollisionComp);

    // Load a default sphere mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        MeshComp->SetStaticMesh(SphereMesh.Object);
        MeshComp->SetRelativeScale3D(FVector(0.1f)); // Scale down the mesh
    }

    // Set up material for the sphere
    static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    if (SphereMaterial.Succeeded())
    {
        MeshComp->SetMaterial(0, SphereMaterial.Object);
    }

    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    // Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
}

void AdanganronpaProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Only add impulse and destroy projectile if we hit a physics object
    if (OtherActor && OtherActor->IsA(AMyTriggerBox::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile hit a trigger box"));

        AMyTriggerBox* TriggerBox = Cast<AMyTriggerBox>(OtherActor);
        if (TriggerBox)
        {
            TriggerBox->OnTriggerHit();
        }
    }

    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

        Destroy();
    }
}

