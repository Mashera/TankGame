// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, 1 is max up movement
	void Elevate(float RelativeSpeed);



private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 30;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = -10;

};
