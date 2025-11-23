// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PlayerCharacter;

class IMMERSIVE_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnInteractionRangeEntered() = 0;
	virtual void OnInteractionRangeExited() = 0;
	virtual void OnInteracted(PlayerCharacter* Player) = 0;
	virtual void HandleInteraction(PlayerCharacter* Player) = 0;
	virtual bool CanBeInteracted() const = 0;
};
