// Fill out your copyright notice in the Description page of Project Settings.


#include "GemItem.h"
#include <SideScroller2D/MyPaperCharacter.h>

AGemItem::AGemItem()
{
	UPaperFlipbook* Gem = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/maps/SunnylandAssets/sprites/gem/gem.gem'")).Object;

	if (Gem != nullptr)
	{
		SpriteComponent->SetFlipbook(Gem);
	}

	UE_LOG(LogTemp, Warning, TEXT("DROPPED GEM"));
}

void AGemItem::AddPowerup(AActor* OtherActor)
{
	if (AMyPaperCharacter* Player = Cast<AMyPaperCharacter>(OtherActor))
	{
		Player->SetPowerup(EItems::eFirerate,5.0f);
	}
}