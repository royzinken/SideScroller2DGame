// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <SideScroller2D/enemy/EnemyActor.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereRadius = 3.0f;
	MaxSpeed = 500.0f;
	InitialSpeed = 300.0f;
	Damage = 20.0f;


	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(SphereRadius);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetGenerateOverlapEvents(true);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->InitialSpeed = InitialSpeed;
	MovementComponent->MaxSpeed = MaxSpeed;

	ProjectileAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/Sprites/Fireball/FB.FB'")).Object;

	SpriteComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComponent->SetFlipbook(ProjectileAnimation);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyActor* Target = Cast<AEnemyActor>(OtherActor)) 
	{
		UCapsuleComponent* CapsComp = Cast<UCapsuleComponent>(OtherComp);

		if (CapsComp)
		{
			Target->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
			Destroy();
		}
	}

}