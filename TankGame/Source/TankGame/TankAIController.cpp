// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI cannot find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI found %s"), *PlayerTank->GetName());
	}
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI not posessing"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Controlling %s"), *ControlledTank->GetName());
	}

}


ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());//returns tank controlled my the AI
}

ATank* ATankAIController::GetPlayerTank() const{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();//gets the player tank
	if (!PlayerTank) { return nullptr; }//prevents error
	return Cast<ATank>(PlayerTank);


}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	
}
