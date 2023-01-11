#include "SaveProteinData.h"

USaveProteinData::USaveProteinData() {

}

void USaveProteinData::AddAlignmentToMap(int key, FAlignment alignment) {
	alignmentMap.Add(key, alignment);
}

FAlignment* USaveProteinData::GetAlignmentFromMap(FPairIdentifier identifier) {
	return alignmentMap.Find(identifier.pairIdentifier);
}
