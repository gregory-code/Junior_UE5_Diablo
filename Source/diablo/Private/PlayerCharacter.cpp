// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" // have to include headers
#include "Camera/CameraComponent.h"
#include "InventoryComponent.generated.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/InventoryWidget.h"
#include "DiabloPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	//inventoryComp = CreateDefaultSubobject<UInventoryComponent>("Inventory Component"); need the inventory component

	cameraBoom->SetupAttachment(GetRootComponent());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 500.0f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(1080.0f);

	GetCharacterMovement()->JumpZVelocity = 600.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	inventoryInputAction->bTriggerWhenPaused = true;
	FInputModeGameOnly input;
	GetWorld()->GetFirstPlayerController()->SetInputMode(input);
}

void APlayerCharacter::PawnClientRestart() // Treating this as begin play ???
{
	Super::PawnClientRestart();

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSystem->ClearAllMappings();
		InputSystem->AddMappingContext(inputMapping, 0);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(moveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(lookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhancedInputComponent->BindAction(jumpInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		enhancedInputComponent->BindAction(inventoryInputAction, ETriggerEvent::Started, this, &APlayerCharacter::Inventory);
	}
}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.Y * GetMoveFwdDir() + input.X * GetMoveRightDir());
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	AddControllerYawInput(input.X);
	AddControllerPitchInput(-input.Y);
}

void APlayerCharacter::Inventory()
{
	if (MyPlayerController == nullptr)
	{
		MyPlayerController = Cast<ADiabloPlayerController>(GetController());
	}

	if (MyPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, missing controller"), *GetName());
		return;
	}

	bInventory = !bInventory;
	MyPlayerController->ToggleInventory(bInventory);
}

FVector APlayerCharacter::GetMoveFwdDir() const
{
	FVector CameraFwd = viewCamera->GetForwardVector();
	CameraFwd.Z = 0;

	return CameraFwd.GetSafeNormal();
}

FVector APlayerCharacter::GetMoveRightDir() const
{
	return viewCamera->GetRightVector();
}