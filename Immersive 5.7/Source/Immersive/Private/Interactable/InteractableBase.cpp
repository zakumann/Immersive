// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInteractableBase::AInteractableBase()
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

	static ConstructorHelpers::FClassFinder<UUserWidget>InteractionWidgetClassFinder(TEXT("/Game/Blueprints/WBP_InteractionWidget"));
	if (InteractionWidgetClassFinder.Succeeded())
	{
		InteractionWidgetComponent->SetWidgetClass(InteractionWidgetClassFinder.Class);
	}
}

void AInteractableBase::OnInteractionRangeEntered()
{
	if (InteractionWidgetComponent)
		InteractionWidgetComponent->SetHiddenInGame(false, true);
}

void AInteractableBase::OnInteractionRangeExited()
{
	if (InteractionWidgetComponent)
		InteractionWidgetComponent->SetHiddenInGame(true, true);
}

void AInteractableBase::OnInteracted(PlayerCharacter* Player)
{
	if (CanBeInteracted())
	{
		HandleInteraction(Player);
	}
}

void AInteractableBase::HandleInteraction(PlayerCharacter* Player)
{
	// Override in child classes

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AInteractableBase::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AInteractableBase::OnEndOverlap);
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBase::OnBeginOverlap(AActor* OverlappedActor, AActor* OtehrActor)
{
	OnInteractionRangeEntered();
}

void AInteractableBase::OnEndOverlap(AActor* OverlappedActor, AActor* OtehrActor)
{
	OnInteractionRangeExited();
}

