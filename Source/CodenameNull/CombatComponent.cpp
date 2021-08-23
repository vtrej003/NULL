// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	IsDead = false;
	CurrentHealth = MaxHealth;
	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!Owner) {
		return;
	}
	Owner->OnTakeAnyDamage.AddDynamic(this, &UCombatComponent::HandleTakeDamage);
	if (Owner->OnTakeAnyDamage.IsBound()) {
		FString debug = "Combat component initialized on " + Owner->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, debug);
	}
}

void UCombatComponent::HandleTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, "took damage " +  FString::SanitizeFloat(Damage));
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	if (CurrentHealth == 0.0f && !IsDead) {
		OnDeath.Broadcast();
		IsDead = true;
	}
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UCombatComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UCombatComponent::GetMaxHealth()
{
	return MaxHealth;
}

