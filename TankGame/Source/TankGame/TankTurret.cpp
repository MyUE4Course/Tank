// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::RotateTurret(float RotateSpeed) {

	auto RotationChange = RotateSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Roll + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}

