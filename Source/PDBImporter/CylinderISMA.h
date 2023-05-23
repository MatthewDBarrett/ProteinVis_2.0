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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CylinderISMA.generated.h"

UCLASS()
class PDBIMPORTER_API ACylinderISMA : public AActor
{
	GENERATED_BODY()
	
public:	
	ACylinderISMA();

	void InstanceConnection(FTransform instanceTransform);

	void SetPosition(FVector position);

	//UPROPERTY(VisibleAnywhere)
	UPROPERTY(VisibleDefaultsOnly)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, Category = MyCharacter)
	int32 ConnectionsISM_index;

	void SetIndex(int32 index);

protected:
	virtual void BeginPlay() override;
};
