#include "InstancedStaticMeshActor.h"
#include "GameFramework/Actor.h"

AInstancedStaticMeshActor::AInstancedStaticMeshActor() {
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	SetRootComponent(InstancedStaticMeshComponent);
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Static);
	InstancedStaticMeshComponent->SetCollisionProfileName("Pawn");
}

void AInstancedStaticMeshActor::InstanceAtom(FTransform instanceTransform) {
	InstancedStaticMeshComponent->AddInstance( instanceTransform );
}

void AInstancedStaticMeshActor::RemoveInitialInstance() {
	if ( InstancedStaticMeshComponent != NULL )
		InstancedStaticMeshComponent->RemoveInstance(0);
}

void AInstancedStaticMeshActor::RemoveAllIntances() {
	for (int i = 0; i < InstancedStaticMeshComponent->GetInstanceCount(); i++) {
		InstancedStaticMeshComponent->RemoveInstance(i);
	}
}

void AInstancedStaticMeshActor::UpdateAtomPosition(std::vector<std::vector<double>> atomPositions, double atomSize, int atomIndex, FVector proteinCentre, int32 simulationScale) {
		FTransform t;

		FVector position = FVector(atomPositions[atomIndex][0] - proteinCentre.X, atomPositions[atomIndex][1] - proteinCentre.Y, atomPositions[atomIndex][2] - proteinCentre.Z);
		position = FVector(position.X * simulationScale, position.Y * simulationScale, position.Z * simulationScale);

		t = FTransform(FRotator(0, 0, 0), position, FVector(atomSize, atomSize, atomSize));

		if (atomIndex == InstancedStaticMeshComponent->GetInstanceCount() -1) {
			InstancedStaticMeshComponent->UpdateInstanceTransform(atomIndex, t, false, true, true);
		}	else {
			InstancedStaticMeshComponent->UpdateInstanceTransform(atomIndex, t, false, false, true);
		}		
}

void AInstancedStaticMeshActor::SetCustomData(int32 index, int32 dataIndex, double dataValue, bool stateDirty) {
	InstancedStaticMeshComponent->SetCustomDataValue(index, dataIndex, dataValue, stateDirty);
}

void AInstancedStaticMeshActor::SetPosition(FVector position) { SetActorLocation(position); }



void AInstancedStaticMeshActor::SetIndex(int32 index) {	AtomsISM_index = index; }

void AInstancedStaticMeshActor::BeginPlay() {
	Super::BeginPlay();
}

void AInstancedStaticMeshActor::RemoveAllAtoms() {
	InstancedStaticMeshComponent->ClearInstances();
}




