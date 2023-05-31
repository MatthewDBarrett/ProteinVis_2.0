/**********************************************************************************
 * Pre-Process
 *
 * Handles actor pooling for the following actors:
 * 
 * - Proteins (groups of molecules)
 * - Molecules
 * ________________________________________________________________________________
 *
 * This file is part of the ProteinVis project.
 *
 * Author:			Matthew Barrett
 *
 * Organisation:	University of Technology Sydney
 *
 * ProteinVis. is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * GNU General Public License V3, 29 June 2007.
 *
 * ProteinVis. is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * <https://www.gnu.org/licenses/gpl-faq.html/>
 *
 * For commercial licensing inquiries and restrictions, please contact either:
 * matthew.barrett@uts.edu.au
 * nico.pietroni@uts.edu.au
 **********************************************************************************/

#include "PreProcess.h"
#include "Molecule.h"
#include <PoolManager/Public/PoolManagerBPLibrary.h>
#include <PoolManager/Public/PoolActorInterface.h>
#include "ProcessPDB.h"

// Sets default values
APreProcess::APreProcess() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APreProcess::BeginPlay() {
	Super::BeginPlay();

	this->InitialiseVariables();

	if ( proteinToSpawn != nullptr )
		UPoolManagerBPLibrary::WarmUp(GetWorld(), proteinToSpawn, proteinPoolSize);

	if (moleculeToSpawn != nullptr)
		UPoolManagerBPLibrary::WarmUp(GetWorld(), moleculeToSpawn, moleculePoolSize);
}

// Called every frame
void APreProcess::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APreProcess::InitialiseVariables() {
	proteinPoolSize = 100;
	moleculePoolSize = 500;
}

void APreProcess::OnPoolBegin_Implementation() {
	IPoolActorInterface::OnPoolBegin_Implementation();
	// Setup the actor after getting fetched from the pool
}

void APreProcess::OnPoolEnd_Implementation() {
	IPoolActorInterface::OnPoolEnd_Implementation();
	// Set the actor to its inactive state
}

