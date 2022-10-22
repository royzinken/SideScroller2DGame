// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_API AItem : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	AItem();

	UPROPERTY(EditAnywhere, Category = Pickup)
		UBoxComponent* BaseCollisionComponent;

	UPROPERTY(EditAnywhere, Category = Sprite)
		UPaperFlipbookComponent* SpriteComponent;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ItemUseEffect;

	virtual void BeginPlay() override;

	virtual void AddScore(AActor* OtherActor);
	virtual void PickupAnimation(AActor* OtherActor);
	virtual void AddPowerup(AActor* OtherActor);

	FTimerHandle MemberTimerHandle;
	void DestroyActor();

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
