#pragma once

#include "CoreMinimal.h"
#include "HClustering/fastcluster.h"
#include "HierarchicalClustering.generated.h"


class PDBIMPORTER_API HierarchicalClustering
{
public:
	HierarchicalClustering();
	~HierarchicalClustering();

	void ClusterMatrix(double* distMatrix, int32 nPoints);
};

USTRUCT()
struct FMatrixRow
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<double> row;

	FMatrixRow() {
		row = {};
	}
};

