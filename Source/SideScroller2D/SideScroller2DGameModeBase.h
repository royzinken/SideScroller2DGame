// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SideScroller2DGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_API ASideScroller2DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
public:
	ASideScroller2DGameModeBase();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
	
};
