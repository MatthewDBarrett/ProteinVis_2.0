#include "HierarchicalClustering.h"
#include "HClustering/fastcluster.h"

HierarchicalClustering::HierarchicalClustering() {
}

HierarchicalClustering::~HierarchicalClustering() {
}

void HierarchicalClustering::ClusterMatrix(double* distMatrix, int32 nPoints) {

	int32* merge = new int[2 * (nPoints - 1)];
	double* height = new double[nPoints - 1];

	int opt_method = HCLUST_METHOD_SINGLE;

	int test = nPoints;

	//hclust_fast(test, distMatrix, opt_method, merge, height);
}
