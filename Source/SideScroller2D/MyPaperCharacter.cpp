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

	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
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
		playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		DrawDebugLine(GetWorld(), MyCharacterPosition, mouseLocation, FColor::Red);
		DrawDebugPoint(GetWorld(), mouseLocation,10.0f,FColor::Red);
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
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPaperCharacter::SpawnProjectile);
}
void AMyPaperCharacter::SpawnProjectile()
{


	FVector mouseLocation, mouseDirection;

	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	if (playerController)
	{
		playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		//DrawDebugLine(GetWorld(), MyCharacterPosition, mouseLocation, FColor::Red, true, 1.0f);

		//UE_LOG(LogTemp, Warning, TEXT("Mouse location:%s"), *mouseLocation.ToString());
	}


	mouseLocation.Y = 0.0f;


	FRotator MyCharacterRotation = Controller->GetControlRotation();

	AProjectile* SpawnedActor1 = (AProjectile*)GetWorld()->SpawnActor(AProjectile::StaticClass(), &mouseLocation, &MyCharacterRotation);

	//SpawnedActor1->SetActorLocation()

	//UE_LOG(LogTemp, Warning, TEXT("MouseLocation :%s MouseDirection:%s"), *mouseLocation.ToString(), *mouseDirection.ToString());


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