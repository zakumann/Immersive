// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractablesInterface.h"
#include "InteractablesBase.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class IMMERSIVE_API AInteractablesBase : public AActor, public IInteractablesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablesBase();

	virtual void OnInteractionRangeEntered() override;
	virtual void OnInteractionRangeExited() override;
	virtual void OnInteracted(APlayerCharacter* PlayerCharacter) override;
	virtual void HandleInteraction(APlayerCharacter* PlayerCharacter) override;
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
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
