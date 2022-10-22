// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectiles/Projectile.h"
#include "GemItem.h"
#include <SideScroller2D/enemy/EnemyActor.h>

AMyPaperCharacter::AMyPaperCharacter()
{

	m_FireRate = m_DefaultFireRate;
	m_Powerup = EItems::eNone;

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleRadius(8.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(13.5f);

	// Create a camera boom attached to the root (capsule)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10;

	// Create an orthographic camera (no perspective) and attach it to the boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	SpringArm->SetUsingAbsoluteRotation(true);
	Camera->bUsePawnControlRotation = false;
	Camera->bAutoActivate = true;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MaxFlySpeed = 300.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	SpringArm->AddWorldRotation(FRotator(0.0f, 90.0f,0.0f));

	IdleAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("/Game/maps/SunnylandAssets/sprites/player/idle/player-idle.player-idle")).Object;

	RunningAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/maps/SunnylandAssets/sprites/player/run/player-run.player-run'")).Object;
	
	FallAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/maps/SunnylandAssets/sprites/player/jump/player-jump.player-jump'")).Object;

}

void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	playerController = GetWorld()->GetFirstPlayerController();
}

void AMyPaperCharacter::SetPowerup(EItems::Powerup powerUp, float duration)
{
	//No stacking of powerups
	if (m_Powerup == powerUp)
		return;

	m_Powerup = powerUp;
	m_PowerupDuration = duration;


	switch (m_Powerup){
		case EItems::eFirerate: { m_FireRate = 0.05f; this->StartShooting() ;break; } 
	}


	GetWorldTimerManager().SetTimer(PowerupTimeHandle, this, &AMyPaperCharacter::RemovePowerup, m_PowerupDuration, false);
}
void AMyPaperCharacter::RemovePowerup()
{
	switch (m_Powerup) {
	case EItems::eFirerate: { m_FireRate = m_DefaultFireRate; this->StartShooting(); } break;
	}

	m_Powerup = EItems::eNone;
	m_PowerupDuration = m_DefaultPowerupDuration;
}

//////////////////////////////////////////////////////////////////////////
// Animation
void AMyPaperCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;

	if (GetCharacterMovement()->IsFalling()) {
		DesiredAnimation = FallAnimation;
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AMyPaperCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();

	FVector mouseLocation, mouseDirection;

	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	if (playerController)
	{
		FHitResult Hitted;

		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, Hitted);

		DrawDebugLine(GetWorld(), MyCharacterPosition, Hitted.Location, FColor::Red);
		DrawDebugPoint(GetWorld(), Hitted.Location,10.0f,FColor::Red);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyPaperCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPaperCharacter::MoveRight);
	PlayerInputComponent->BindAction("DropGem", IE_Released, this, &AMyPaperCharacter::DropGem);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPaperCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyPaperCharacter::StopShooting);
}
void AMyPaperCharacter::StartShooting()
{
	if (PlayerState != EPlayerStates::shooting || m_Powerup == EItems::eFirerate)
	{
	
		GetWorldTimerManager().SetTimer(TimeHandle, this, &AMyPaperCharacter::SpawnProjectile, m_FireRate, true);
		PlayerState = EPlayerStates::shooting;
	}
}
void AMyPaperCharacter::StopShooting()
{
	if (PlayerState == EPlayerStates::shooting)
	{
		GetWorldTimerManager().ClearTimer(TimeHandle);
		PlayerState = EPlayerStates::idl;
	}
}
void AMyPaperCharacter::SpawnProjectile()
{

	if (playerController)
	{
		FHitResult HitLocation;
		FRotator Rotation;

		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, HitLocation);

		HitLocation.Location.Y = 0.0f;

		FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		FVector Pointer = (HitLocation.Location - MyCharacterPosition);

		Pointer.Normalize();

		Rotation = Pointer.Rotation();


		AProjectile* SpawnedActor1 = (AProjectile*)GetWorld()->SpawnActor(AProjectile::StaticClass(), &MyCharacterPosition, &Rotation);
	}
}
void AMyPaperCharacter::DropGem()
{

	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;

	if (Controller != nullptr)
	{
		FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FRotator MyCharacterRotation = Controller->GetControlRotation();


		MyCharacterPosition.X = (MyCharacterRotation.Yaw == 180.0f) ? MyCharacterPosition.X - 50.0f : MyCharacterPosition.X + 50.0f;
		AGemItem* SpawnedActor1 = (AGemItem*)GetWorld()->SpawnActor(AGemItem::StaticClass(), &MyCharacterPosition, &MyCharacterRotation);
	}
	UE_LOG(LogTemp, Warning, TEXT("DROPPED"));
}
void AMyPaperCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(-1.0f, 0.0f, 0.0f), Value);
}

void AMyPaperCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}