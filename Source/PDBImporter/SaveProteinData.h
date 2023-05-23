/**********************************************************************************
 * Save Protein Data
 *
 * Used for saving of alignment data for molecules.
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
#include "GameFramework/SaveGame.h"
#include "ProcessPDB.h"
#include "SaveProteinData.generated.h"

UCLASS()
class PDBIMPORTER_API USaveProteinData : public USaveGame
{
	GENERATED_BODY()

public:

	USaveProteinData();

	UPROPERTY(VisibleAnywhere)
	TMap<int, FAlignment> savedAlignmentMap;

	UPROPERTY(VisibleAnywhere)
	TArray<int32> atomAmount;

	void AddAlignmentToMap(int key, FAlignment alignment);

	//FAlignment* GetAlignmentFromMap(FPairIdentifier identifier);

	bool isAlignmentMapValid();

	TMap<int, FAlignment> GetAlignmentMap();

	void SetAlignmentMap(TMap<int, FAlignment> map);

	UPROPERTY(VisibleAnywhere)
	int32 testNum;

	void SetTestNum(int32 value);

	//bool Save(int key, FAlignment alignment);
	//static USaveProteinData* Load();

private:

};
