// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_light.h"


AInteractable_light::AInteractable_light()
{
	State = true;
	Intensity = 100000.0f;
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetIntensity(Intensity);
}

void AInteractable_light::Interact()
{
	if(State)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(Intensity);
	}
	State = !State;
}


