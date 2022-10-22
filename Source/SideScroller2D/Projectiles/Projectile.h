// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.generated.h"

UCLASS()
class SIDESCROLLER2D_API AProjectile : public APaperFlipbookActor
{
	GENERATED_BODY()
protected:
	float SphereRadius;
	float MaxSpeed;
	float InitialSpeed;
	float Damage;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, Category = Projectile)
		USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = Sprite)
		UPaperFlipbookComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, Category = Projectile)
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY()
		class UPaperFlipbook* ProjectileAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
