// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../enemy/EnemyActor.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS( Abstract)
class SIDESCROLLER2D_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void  SetOwnerEnemy(AEnemyActor* enemy) { OwnerEnemy = enemy; };

protected:
	TWeakObjectPtr<AEnemyActor> OwnerEnemy;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHealthLabel;

public:
		virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;
};
