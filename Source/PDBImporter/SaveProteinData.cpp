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
