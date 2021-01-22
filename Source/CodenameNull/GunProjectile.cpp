// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectile.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "DrawDebugHelpers.h"

//AGunProjectile::AGunProjectile(float initialSpeed, float maxSpeed, bool bRotationFollowsVelocity, bool bShouldBounce, float bounciness, float projectileGravityScale)
//{
//	AGunProjectile::AGunProjectile() :AGunProjectile(3000.0f, 3000.0f, true, true, 0) {}
//}

// Sets default values

AGunProjectile::AGunProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Event called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &AGunProjectile::OnHit);
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(50.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
		CollisionComponent->SetNotifyRigidBodyCollision(true);
	}
	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/ThirdPersonCPP/Blueprints/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;
	Damage = 1.0f;
}

// Called when the game starts or when spawned
void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void AGunProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function that is called when the projectile hits something.
void AGunProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, "hit something");
	if (OtherActor != this)
	{
		if (OtherComponent->IsSimulatingPhysics())
			OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		else 
			UGameplayStatics::ApplyPointDamage(OtherActor, Damage, GetVelocity().GetSafeNormal(), Hit, GetInstigatorController(), this, UDamageType::StaticClass());
	}

	Destroy();
}

