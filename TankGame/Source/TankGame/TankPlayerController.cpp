// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find aiming component at begin play"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	FVector HitLocation; //OutParameter
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	if (GetSightRayHitLocation(HitLocation))  // has side-effect, is going to line-trace
	{ 
		AimingComponent->AimAt(HitLocation);
	}


	//if it hits the landscape, tell controlled tank to aim at this point


}

//Get wolrd location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;



	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Shows the position of the crosshair in pixel coordinates.
	auto ScreenLocation = FVector2D(ViewportSizeX* CrossHairXLocation, ViewportSizeY * CrossHairYLocation); 

	//"De-project" screen position of cursor/crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along the look-direction, see what is it (up to max range of X)
		GetLookVectorHitLocation(LookDirection, HitLocation);

	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const 
{
	FVector CameraWorldLocation; // to be discarded

	DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location; // set
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.Location.ToString());
			return true;
	}
	HitLocation = FVector(0.f);
	return false; // didn't hit anything
}