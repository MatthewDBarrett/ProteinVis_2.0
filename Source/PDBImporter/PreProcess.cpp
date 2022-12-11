#include "PreProcess.h"
#include "Molecule.h"
#include "ProcessPDB.h"

// Sets default values
APreProcess::APreProcess() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APreProcess::BeginPlay() {
	Super::BeginPlay();
	
	//for (int i = 0; i < 10; i++) {
	//	proteinPool[i]->GenerateMoleculeColours(false);
	//	proteinPool[i]->SetFolder("");
	//	proteinPool[i]->LoadPDBfromFile("1bna");
	//}
}

// Called every frame
void APreProcess::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APreProcess::OnPoolBegin_Implementation() {
	IPoolActorInterface::OnPoolBegin_Implementation();
	// Setup the actor after getting fetched from the pool
}

void APreProcess::OnPoolEnd_Implementation() {
	IPoolActorInterface::OnPoolEnd_Implementation();
	// Set the actor to its inactive state
}

