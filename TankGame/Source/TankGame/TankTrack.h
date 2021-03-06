// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 TankTrack is used to set maximum driving force and to apply forces to the tank. 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce =  600000; //A 60 ton tank, 1G of acceleration.
	
private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();
	void DriveTrack();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
