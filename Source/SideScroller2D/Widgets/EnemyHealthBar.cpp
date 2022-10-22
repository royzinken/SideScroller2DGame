// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UEnemyHealthBar::NativeTick(const FGeometry& MyGeometry, float inDeltaTime)
{
	Super::NativeTick(MyGeometry, inDeltaTime);

	if (!OwnerEnemy.IsValid())
		return;

	if (OwnerEnemy->GetHealth() <= 0)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	HealthBar->SetPercent(OwnerEnemy->GetHealth() / OwnerEnemy->GetMaxHealth());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);

	CurrentHealthLabel->SetText(FText::AsNumber(OwnerEnemy->GetHealth(), &Opts));
	MaxHealthLabel->SetText(FText::AsNumber(OwnerEnemy->GetMaxHealth(), &Opts));
}