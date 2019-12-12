// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "Tank.h"
// #include "Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


private:
	ATank* GetControlledTank() const;
	
	// Start the tank moving the barrel so that a shot would hit 
	// where the crosshairs intersects the world
	void AimTowardsCrosshair();

	// Return OUOT parameter, true if hit landscape

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
	// FHitResult HitLocation;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;



	/* UPROPERTY(EditAnywhere)
	float LineTraceRange = 10.f;
	bool GetLookVectorHitLocation(FVector &LookDirection);
	FHitResult HitLocation;*/ 

/* public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};
