// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Posessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
	// UE_LOG(LogTemp, Warning, TEXT("Logging Tick"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {	return;	}

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has a "side effect", is going to line trace
	{
		// TankAimingComponent->AimAt(FVector(3));
		// UTankAimingComponent::AimAt(HitLocation);
		// TankAimingComponent()
		// AimAt(HitLocation);
		GetControlledTank()->AimAt(HitLocation);
		// TODO Tell controlled tank to aim at this point
	}
}

// Get world location if you linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of a crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);

		/// if (GetLookVectorHitLocation(LookDirection))
		///{
		///}
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	// UE_LOG(LogTemp, Warning, TEXT("Start Location: %s"), *StartLocation.ToString());
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

/* bool ATankPlayerController::GetLookVectorHitLocation(FVector &LookDirection)
{
	if (GetControlledTank())
	{
		// GetWorld()->GetFirstPlayerController()->GetActorLocation();
		// return GetWorld()->LineTraceSingleByChannel(HitLocation, GetControlledTank()->GetActorLocation(), GetControlledTank()->GetActorLocation()+LookDirection+LineTraceRange, ECC_Visibility);
		return GetWorld()->LineTraceSingleByChannel(HitLocation, GetControlledTank()->GetActorLocation(), GetControlledTank()->GetActorLocation()+(LookDirection.X+LineTraceRange), ECC_Visibility);
	}
	else
	{
		return false;
	}
}*/

