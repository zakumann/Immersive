// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InteractablesBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInteractablesBase::AInteractablesBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	RootComponent = InteractableMesh;

	InteractionRange = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionRange"));
	InteractionRange->InitSphereRadius(200.f);
	InteractionRange->SetupAttachment(InteractableMesh);

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractionWidgetComponent->SetupAttachment(InteractableMesh);
	InteractionWidgetComponent->SetDrawAtDesiredSize(true);
	InteractionWidgetComponent->SetHiddenInGame(true, true);
}

void AInteractablesBase::OnInteractionRangeEntered()
{
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetHiddenInGame(false, true);
	}
}

void AInteractablesBase::OnInteractionRangeExited()
{
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetHiddenInGame(true, true);
	}
}

void AInteractablesBase::OnInteracted(APlayerCharacter* PlayerCharacter)
{
	if (CanBeInteracted())
	{
		HandleInteraction(PlayerCharacter);
	}
}

void AInteractablesBase::HandleInteraction(APlayerCharacter* PlayerCharacter)
{
	// Override in child classes
}

// Called when the game starts or when spawned
void AInteractablesBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AInteractablesBase::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AInteractablesBase::OnEndOverlap);
}

// Called every frame
void AInteractablesBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractablesBase::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OnInteractionRangeEntered();
}

void AInteractablesBase::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OnInteractionRangeExited();
}

