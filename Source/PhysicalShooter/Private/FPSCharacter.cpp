// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/CharacterGameplayAbility.h"
#include "Abilities/AttributeSets/CharacterStatsAttributeSet.h"
#include "GameplayEffectTypes.h"

AFPSCharacter::AFPSCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UCharacterStatsAttributeSet>(TEXT("AttributeSet"));
}

bool AFPSCharacter::IsAlive() const
{
	return GetHealth() > 0;
}

int32 AFPSCharacter::GetAbilityLevel(AbilityID ID) const
{
	return 1;
}

void AFPSCharacter::RemoveCharacterAbilities()
{
	if(!AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
		for(const FGameplayAbilitySpec& spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			if(spec.SourceObject == this && CharacterAbilities.Contains(spec.Ability.GetClass()))
			{
				AbilitiesToRemove.Add(spec.Handle);
			}
		}

		for (int i = 0; i < AbilitiesToRemove.Num(); ++i)
		{
			AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
		}
		AbilitySystemComponent->CharacterAbilitiesGiven = false;
	}
}

float AFPSCharacter::GetHealth() const
{
	if(IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float AFPSCharacter::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		HealthChangedDelegatehandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AFPSCharacter::OnHealthChanged);
	}

	InitializeAttributes();
	//AddStartupEffects();
	AddCharacterAbilities();
	SetHealth(GetMaxHealth());
}

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
	}
}

UAbilitySystemComponent* AFPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFPSCharacter::AddCharacterAbilities()
{
	if(!AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		for(const TSubclassOf<UCharacterGameplayAbility>& ability : CharacterAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ability->GetClass()));
		}
		AbilitySystemComponent->CharacterAbilitiesGiven = true;
	}
}

void AFPSCharacter::InitializeAttributes()
{
	if(!IsValid(DefaultAttributes))
	{
		UE_LOG(LogTemp, Log, TEXT("%s() is missing DefaultAttributes for %s. Please fill in character's blueprint"), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle handle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if(handle.IsValid())
	{
		FActiveGameplayEffectHandle activeGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*handle.Data.Get(), AbilitySystemComponent);
	}
}

void AFPSCharacter::AddStartupEffects()
{
	if(!AbilitySystemComponent->StartupEffectsApplied)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for(TSubclassOf<UGameplayEffect> effect : StartupEffects)
		{
			const FGameplayEffectSpecHandle handle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
			if (handle.IsValid())
			{
				FActiveGameplayEffectHandle activeGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*handle.Data.Get(), AbilitySystemComponent);
			}
		}

		AbilitySystemComponent->StartupEffectsApplied = true;
	}
}

void AFPSCharacter::SetHealth(float Health)
{
	if(IsValid(AttributeSet))
	{
		AttributeSet->SetHealth(Health);
	}
}


void AFPSCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Log, TEXT("Health Changed from %f to %f"), Data.OldValue, Data.NewValue);
}

/*
void AFPSCharacter::BindASCInput(UInputComponent* InputComponent)
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(TEXT("ConfirmTarget"), TEXT("CancelTarget"), TEXT("AbilityID"). ))
	}
}
*/

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}