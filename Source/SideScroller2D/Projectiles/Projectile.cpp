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
	InitialSpeed = 500.0f;
	Damage = 25.0f;
	InitialLifeSpan = 3.0f;


	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(SphereRadius);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->InitialSpeed = InitialSpeed;
	MovementComponent->MaxSpeed = MaxSpeed;

	ProjectileAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/Sprites/Fireball/pixil-frame.pixil-frame'")).Object;

	SpriteComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComponent->SetFlipbook(ProjectileAnimation);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyPaperCharacter>(OtherActor))
		return;


	if (AEnemyActor* Target = Cast<AEnemyActor>(OtherActor)) 
	{
		if (!Target->IsAlive())
			return;

		Target->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
	}

	Destroy();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherComp->GetName());
}