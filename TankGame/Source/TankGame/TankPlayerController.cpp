// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not posessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Controlling %s"), *ControlledTank->GetName());
	}

	
}


ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetControlledTank()) { return; }
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
}

