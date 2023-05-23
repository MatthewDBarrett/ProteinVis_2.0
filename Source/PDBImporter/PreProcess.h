/**********************************************************************************
 * Pre-Process
 *
 * Handles actor pooling for the following actors:
 *
 * - Proteins (groups of molecules)
 * - Molecuels
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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Molecule.h"
#include "ProcessPDB.h"
#include <PoolManager/Public/PoolManagerBPLibrary.h>
#include <PoolManager/Public/PoolActorInterface.h>
#include "PreProcess.generated.h"

UCLASS()
class PDBIMPORTER_API APreProcess : public AActor, public IPoolActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreProcess();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> moleculeToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> proteinToSpawn;

	//UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	//TSubclassOf<AActor> myAtomMeshToSpawn;
	//UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	//TSubclassOf<AActor> myConnectionMeshToSpawn;

	int32 moleculePoolSize;
	int32 proteinPoolSize;
	//int32 atomMeshPoolSize;
	//int32 connectionMeshPoolSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialiseVariables();

	// Called right after spawning or fetching from pool
	virtual void OnPoolBegin_Implementation() override;

	// Called right after the actor is released to the pool
	virtual void OnPoolEnd_Implementation() override;

};
