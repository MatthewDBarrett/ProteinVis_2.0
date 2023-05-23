/**********************************************************************************
 * Spawn Actor
 * [DEPRECATED]
 *
 * Used for spawning an initial actor into a level.
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
#include "SpawnActor.generated.h"

UCLASS()
class PDBIMPORTER_API ASpawnActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> ActorToSpawn;

};