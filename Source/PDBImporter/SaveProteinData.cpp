#include "SaveProteinData.h"

USaveProteinData::USaveProteinData() {
}

//void USaveProteinData::AddAlignmentToMap(int key, FAlignment alignment) {
//	savedAlignmentMap.Add(key, alignment);
//}
//
//FAlignment* USaveProteinData::GetAlignmentFromMap(FPairIdentifier identifier) {
//	return savedAlignmentMap.Find(identifier.pairIdentifier);
//}

bool USaveProteinData::isAlignmentMapEmpty() {
	if (&savedAlignmentMap != nullptr)
		return false;
	else
		return true;
}

TMap<int, FAlignment> USaveProteinData::GetAlignmentMap() { return savedAlignmentMap; }
