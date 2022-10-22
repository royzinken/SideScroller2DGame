// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include <SideScroller2D/Widgets/EnemyHealthBar.h>

AEnemyActor::AEnemyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleRadius(9.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(9.0f);

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarBP(TEXT("WidgetBlueprint'/Game/Blueprints/WBP_HealthBar.WBP_HealthBar'"));

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	HealthWidgetComp->SetupAttachment(RootComponent);
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComp->SetWidgetClass(HealthBarBP.Class);
	HealthWidgetComp->SetDrawAtDesiredSize(true);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(100.0f, 8.0f, 40.0f));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetupAttachment(RootComponent);

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetBoxExtent(FVector(20.0f, 8.0f, 40.0f));
	AttackBox->SetGenerateOverlapEvents(true);
	AttackBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackBox->SetupAttachment(RootComponent);

	IdleAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("/Game/maps/SunnylandAssets/sprites/frog/idle/frog-idle.frog-idle")).Object;

	RunningAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("/Game/maps/SunnylandAssets/sprites/frog/jump/frog-jump.frog-jump")).Object;

	DeadAnimation = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/maps/SunnylandAssets/sprites/enemy-death/enemy-death.enemy-death'")).Object;

	GetSprite()->SetFlipbook(IdleAnimation);
	GetSprite()->SetupAttachment(RootComponent);

	State = EnemyState::eIDL;

	speed = 60.0f;
	Health = DefaultHealth;
}
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	UEnemyHealthBar* HealthBar = Cast<UEnemyHealthBar>(HealthWidgetComp->GetUserWidgetObject());

	HealthBar->SetOwnerEnemy(this);


	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::BeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyActor::OverlapEnd);

	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::BeginOverlapAttack);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyActor::OverlapEndAttack);

	StartLocation = this->GetActorLocation();
}
void AEnemyActor::DestroyActor()
{
	Destroy();
}
void AEnemyActor::Died()
{
	FTimerHandle MemberTimerHandle;

	GetSprite()->SetFlipbook(DeadAnimation);
	CollisionBox->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AEnemyActor::DestroyActor, GetSprite()->GetFlipbookLength(), false);
}
void AEnemyActor::DoAttack()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ATTACK"));
}

float AEnemyActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Health -= DamageAmount;

	if (Health <= 0)
	{
		State = EnemyState::eDead;
		Died();
	}

	return DamageAmount;
}
void AEnemyActor::UpdateAnimation()
{
	switch (State) {
	case EnemyState::ePlayerDetected: { DesiredAnimation = RunningAnimation; }  break;
	case EnemyState::eIDL: { DesiredAnimation = IdleAnimation; } break;
	case EnemyState::eDead: { DesiredAnimation = DeadAnimation; } break;
	default: { DesiredAnimation = IdleAnimation;  } break;
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation) {
		GetSprite()->SetFlipbook(DesiredAnimation);
	}

	if (Direction.X > 0.0f)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0, 180.0f, 0.0f));
	}
	else if (Direction.X < 0.0f)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}
void AEnemyActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateAnimation();

	if (State == EnemyState::ePlayerDetected)
	{

		if (PlayerREF) {

			Direction = PlayerREF->GetActorLocation() - StartLocation;
		
			TotalDistance = Direction.Size();
			Direction = Direction.GetSafeNormal();

			FVector Location = GetActorLocation();

			Location += Direction * speed * DeltaSeconds;
		

			SetActorLocation(Location);

			if (Direction.X < 0)
				CurrentDistance = (Location - StartLocation).Size();
			else
				CurrentDistance = (Location + StartLocation).Size();


			UE_LOG(LogTemp, Warning, TEXT("Direction:%f CurrentDistance:%f"), Direction.X,CurrentDistance);
		}
	}
}

void AEnemyActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyPaperCharacter* otherActor = Cast<AMyPaperCharacter>(OtherActor))
	{
		PlayerREF = Cast<AMyPaperCharacter>(OtherActor);

		CurrentDistance = 0.0f;
		State = EnemyState::ePlayerDetected;
	}
}

void AEnemyActor::OverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMyPaperCharacter* otherActor = Cast<AMyPaperCharacter>(OtherActor))
	{
		State = EnemyState::eIDL;
		StartLocation = this->GetActorLocation();
	}
}

void AEnemyActor::BeginOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyPaperCharacter* otherActor = Cast<AMyPaperCharacter>(OtherActor))
	{
		State = EnemyState::eAttacking;
		StartLocation = this->GetActorLocation();

		DoAttack();
	}
}

void AEnemyActor::OverlapEndAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMyPaperCharacter* otherActor = Cast<AMyPaperCharacter>(OtherActor))
	{
		State = EnemyState::ePlayerDetected;
	}
}

