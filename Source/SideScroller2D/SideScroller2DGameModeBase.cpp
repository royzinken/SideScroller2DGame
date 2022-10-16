// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideScroller2DGameModeBase.h"
#include "SideScroller2D.h"
#include "MyHUD.h"
#include "MyPaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ASideScroller2DGameModeBase::ASideScroller2DGameModeBase()
{
	// Set default pawn class to our character
	DefaultPawnClass = AMyPaperCharacter::StaticClass();
}

void ASideScroller2DGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(UGameplayStatics::GetPlayerPawn(this,0));

	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}