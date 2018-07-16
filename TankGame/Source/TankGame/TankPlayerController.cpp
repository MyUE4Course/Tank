// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Tank.h"


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

	return Cast<ATank>(GetPawn());//returns pawn of controlled tank
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetControlledTank()) { return; }
	FVector HitLocation;//creating fvector hit location
	if (GetSightRayHitLocation(HitLocation)) { //passing hitlocation as out parameter to GetSightRayHitLocation

		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	///find crosshair location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {//passing LookDirection as Out parameter
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const {

	///Deproject to screen
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();


}

