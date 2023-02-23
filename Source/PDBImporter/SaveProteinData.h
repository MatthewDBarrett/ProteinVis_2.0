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
