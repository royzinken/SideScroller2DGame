// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "DrawDebugHelpers.h"
#include "MyPaperCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCapsuleComponent"));
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	RootComponent = BaseCollisionComponent;


	FVector BoxSize = FVector(8.0f, 50.0f, 8.0f);

	BaseCollisionComponent->SetBoxExtent(BoxSize);

	BaseCollisionComponent->SetGenerateOverlapEvents(true);
	BaseCollisionComponent->SetSimulatePhysics(true);

	BaseCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BaseCollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	ItemUseEffect = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/maps/SunnylandAssets/sprites/item-feedback/item-feedback.item-feedback'")).Object;

	SpriteComponent->SetupAttachment(BaseCollisionComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::BeginOverlap);
}
void AItem::DestroyActor()
{
	Destroy();
}
void AItem::AddScore(AActor* OtherActor)
{
	AMyPaperCharacter* Character = Cast<AMyPaperCharacter>(OtherActor);

	if (Character != nullptr) 
	{
		int NewScore = Character->GetScore() + 1;

		Character->UpdateScore(NewScore);
	}
}
void AItem::PickupAnimation(AActor* OtherActor)
{
	AMyPaperCharacter* Character = Cast<AMyPaperCharacter>(OtherActor);

	if (Character != nullptr)
	{
		BaseCollisionComponent->SetGenerateOverlapEvents(false);
		SpriteComponent->SetFlipbook(ItemUseEffect);

		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AItem::DestroyActor, SpriteComponent->GetFlipbookLength(), false);
	}

}
void AItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->AddScore(OtherActor);
	this->PickupAnimation(OtherActor);
	this->AddPowerup(OtherActor);

}

void AItem::AddPowerup(AActor* OtherActor)
{

}