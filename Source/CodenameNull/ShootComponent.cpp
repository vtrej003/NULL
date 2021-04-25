// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!Owner) {
		FString debug = "Shoot component initialized on " + Owner->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, debug);
		return;
	}
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShootComponent::Fire(FRotator direction)
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;

		Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards. 
		FRotator MuzzleRotation = direction;
		MuzzleRotation.Pitch += MuzzlePitch;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Owner;
			SpawnParams.Instigator = Owner->GetInstigator();

			// Spawn the projectile at the muzzle.
			AGunProjectile* Projectile = World->SpawnActor<AGunProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->Shooter = Owner;
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}

		}
	}
}

