// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_API AEnemy : public APaperFlipbookActor
{
	GENERATED_BODY()


public:
	AEnemy();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		UCapsuleComponent* BaseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Sprite)
		UPaperFlipbookComponent* SpriteComponent;

	

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

};
