// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Interactable.h"
#include "Components/SpotLightComponent.h"
#include "Interactable_light.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMENULL_API AInteractable_light : public AMaster_Interactable
{
	GENERATED_BODY()

public:
	virtual void Interact() override;

	UPROPERTY()
	bool State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Intensity;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* Light;

	AInteractable_light();
};
