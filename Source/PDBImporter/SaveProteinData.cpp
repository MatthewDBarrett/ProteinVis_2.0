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

#include "SaveProteinData.h"
#include "Kismet/GameplayStatics.h"

USaveProteinData::USaveProteinData() {
}

void USaveProteinData::AddAlignmentToMap(int key, FAlignment alignment) {
	savedAlignmentMap.Add(key, alignment);
}

//FAlignment* USaveProteinData::GetAlignmentFromMap(FPairIdentifier identifier) {
//	return savedAlignmentMap.Find(identifier.pairIdentifier);
//}

bool USaveProteinData::isAlignmentMapValid() {
	if (&savedAlignmentMap != nullptr) {
		return true;
	} else {
		return false;
	}
}

TMap<int, FAlignment> USaveProteinData::GetAlignmentMap() { return savedAlignmentMap; }

void USaveProteinData::SetAlignmentMap(TMap<int, FAlignment> map) {	savedAlignmentMap = map; }

void USaveProteinData::SetTestNum(int32 value)
{
	testNum = value;
}
//
//bool USaveProteinData::Save(int key, FAlignment alignment) {
//	USaveProteinData* SaveGameInstance = Cast<USaveProteinData>(UGameplayStatics::CreateSaveGameObject(USaveProteinData::StaticClass()));
//
//	SaveGameInstance->savedAlignmentMap = savedAlignmentMap;
//	this->AddAlignmentToMap(key, alignment);	
//
//	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MySaveSlot", 0);
//}
//
//USaveProteinData* USaveProteinData::Load() {
//	USaveProteinData* LoadedSaveGame = Cast<USaveProteinData>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
//	if (LoadedSaveGame)
//		return LoadedSaveGame;
//	else
//		return Cast<USaveProteinData>(UGameplayStatics::CreateSaveGameObject(USaveProteinData::StaticClass()));
//
//}
