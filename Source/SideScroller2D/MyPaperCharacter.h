// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "PaperCharacter.h"
#include "MyPaperCharacter.generated.h"

/**
 * 
 */

class UPaperFlipbook;

UCLASS()
class SIDESCROLLER2D_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
private:
	int m_Score = 0;
public:
	AMyPaperCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	virtual void Tick(float DeltaSeconds) override;

	/**Accesor function for score*/
	UFUNCTION(BlueprintPure, Category = "Score")
		int GetScore() { return m_Score; };

	UFUNCTION(BlueprintCallable, Category = "Score")
		void UpdateScore(int score) { m_Score = score; };

	UFUNCTION()
		void SpawnProjectile();
protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FallAnimation;

	UPROPERTY()
		APlayerController* playerController;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	void UpdateCharacter();

	/** Called for side to side input */
	void MoveRight(float Value);

	void DropGem();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

};
