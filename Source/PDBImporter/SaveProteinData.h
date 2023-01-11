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

	UPROPERTY(EditAnywhere)
	TMap<int, FAlignment> alignmentMap;

	void AddAlignmentToMap(int key, FAlignment alignment);

	FAlignment* GetAlignmentFromMap(FPairIdentifier identifier);	
};
