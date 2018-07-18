// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

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
		GetControlledTank()->Fire();
	}
	
}
