// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "../MyPaperCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/WidgetComponent.h"
#include "EnemyActor.generated.h"

enum EnemyState {
	eNone,
	eIDL,
	eAttacking,
	ePlayerDetected,
	eDead
};
/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_API AEnemyActor : public APaperCharacter
{
	GENERATED_BODY()

protected:
	EnemyState State;
	FTimerHandle SeekPlayerTimerHandle;

	FVector Direction;
	FVector StartLocation;
	float TotalDistance;
	float CurrentDistance;
	float speed;
	float Health = 0;
	float DefaultHealth = 100;

	UPROPERTY()
		AMyPaperCharacter* PlayerREF;

public:
	AEnemyActor();

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	float GetHealth() { return Health;  }
	float GetMaxHealth() { return DefaultHealth; }
protected:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void BeginOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEndAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void UpdateAnimation();

	UFUNCTION()
		void DoAttack();

	UFUNCTION()
		void Died();

	UFUNCTION()
		void DestroyActor();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DesiredAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DeadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* AttackBox;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* HealthWidgetComp;

};
