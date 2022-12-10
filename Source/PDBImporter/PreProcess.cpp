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
	
	this->InitializeVariables();
	this->GenerateMoleculePool();
	this->GenerateProteinPool();
	this->GenerateAtomMeshPool();
	this->GenerateConnectionMeshPool();

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

void APreProcess::InitializeVariables() {
	spawnPos = FVector(0, 0, 0);
	spawnRot = FRotator(0, 0, 0);

	proteinPoolSize = 2000;
	moleculePoolSize = 6000;
	atomMeshPoolSize = 1500000;
	connectionMeshPoolSize = 1500000;

}

void APreProcess::GenerateMoleculePool() {
	moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, spawnPos, spawnRot, spawnParams);
	moleculePointer = Cast<AMolecule>(moleculeActor);

	moleculePool.Init(moleculePointer, moleculePoolSize);
}

void APreProcess::GenerateProteinPool() {
	proteinActor = GetWorld()->SpawnActor<AActor>(myProteinToSpawn, spawnPos, spawnRot, spawnParams);
	proteinPointer = Cast<AProcessPDB>(proteinActor);

	proteinPool.Init(proteinPointer, proteinPoolSize);
}

void APreProcess::GenerateAtomMeshPool() {
	atomMeshActor = GetWorld()->SpawnActor<AActor>(myAtomMeshToSpawn, spawnPos, spawnRot, spawnParams);
	atomMeshPointer = Cast<AInstancedStaticMeshActor>(atomMeshActor);

	atomMeshPool.Init(atomMeshPointer, atomMeshPoolSize);
}

void APreProcess::GenerateConnectionMeshPool() {
	connectionMeshActor = GetWorld()->SpawnActor<AActor>(myConnectionMeshToSpawn, spawnPos, spawnRot, spawnParams);
	connectionMeshPointer = Cast<ACylinderISMA>(connectionMeshActor);

	connectionMeshPool.Init(connectionMeshPointer, connectionMeshPoolSize);
}

