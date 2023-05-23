/**********************************************************************************
 * Cylinder ISMA (Instanced Static Mesh Actor)
 *
 * Instatiates and provides access to the clyinder/connection ISMs 
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

#include "CylinderISMA.h"

ACylinderISMA::ACylinderISMA()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	SetRootComponent(InstancedStaticMeshComponent);
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Static);
	InstancedStaticMeshComponent->SetCollisionProfileName("Pawn");
}

void ACylinderISMA::InstanceConnection(FTransform instanceTransform) {
	InstancedStaticMeshComponent->AddInstance(instanceTransform);
}

void ACylinderISMA::SetPosition(FVector position) {
	SetActorLocation(position);
}

void ACylinderISMA::SetIndex(int32 index) { ConnectionsISM_index = index; }

void ACylinderISMA::BeginPlay()
{
	Super::BeginPlay();
	
}

