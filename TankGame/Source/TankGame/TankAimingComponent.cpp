// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurret(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	auto BarrrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) {
	
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->RotateTurret(DeltaRotator.GetNormalized().Yaw);

}