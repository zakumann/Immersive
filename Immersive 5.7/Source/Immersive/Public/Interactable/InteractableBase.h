// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Immersive/Interface/InteractableInterface.h"
#include "InteractableBase.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class IMMERSIVE_API AInteractableBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	virtual void OnInteractionRangeEntered() override;
	virtual void OnInteractionRangeExited() override;
	virtual void OnInteracted(PlayerCharacter* Player) override;
	virtual void HandleInteraction(PlayerCharacter* Player) override;
	virtual bool CanBeInteracted() const { return true; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InteractionRange = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* InteractableMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UWidgetComponent* InteractionWidgetComponent = nullptr;

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtehrActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtehrActor);
};
