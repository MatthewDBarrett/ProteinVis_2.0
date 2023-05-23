/**********************************************************************************
 * Instanced Static Mesh Actor (ISMA) - Atoms
 *
 * Instatiates and provides access to the atom ISMs
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
#include "InstancedStaticMeshActor.generated.h"

UCLASS()
class PDBIMPORTER_API AInstancedStaticMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AInstancedStaticMeshActor();

	UInstancedStaticMeshComponent *ISMComp;

	void InstanceAtom(FTransform instanceTransform);

	void RemoveInitialInstance();

	void RemoveAllIntances();

	void UpdateAtomPosition(std::vector<std::vector<double>> atomPositions, double atomSize, int atomIndex, FVector proteinCentre, int32 simulationScale);

	void SetCustomData(int32 index, int32 dataIndex, double dataValue, bool stateDirty);

	void SetPosition(FVector position);

	void RemoveAllAtoms();

	UPROPERTY(BlueprintReadWrite, Category = MyCharacter)
	int32 AtomsISM_index;

	void SetIndex(int32 index);

	UStaticMesh* StaticMesh;

	//UPROPERTY(VisibleAnywhere)
	//UPROPERTY(VisibleDefaultsOnly)
	UPROPERTY(BlueprintReadWrite, Category = MyCharacter)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

protected:

	virtual void BeginPlay() override;
};
