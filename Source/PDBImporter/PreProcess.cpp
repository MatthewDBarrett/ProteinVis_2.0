#include "PreProcess.h"
#include "Molecule.h"
#include <PoolManager/Public/PoolManagerBPLibrary.h>
#include <PoolManager/Public/PoolActorInterface.h>
#include "ProcessPDB.h"

// Sets default values
APreProcess::APreProcess() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APreProcess::BeginPlay() {
	Super::BeginPlay();

	this->InitialiseVariables();

	if ( proteinToSpawn != nullptr )
		UPoolManagerBPLibrary::WarmUp(GetWorld(), proteinToSpawn, proteinPoolSize);

	if (moleculeToSpawn != nullptr)
		UPoolManagerBPLibrary::WarmUp(GetWorld(), moleculeToSpawn, moleculePoolSize);

	
	
	//for (int i = 0; i < 10; i++) {
	//	FTransform transform = FTransform(FRotator(0, 0, 0), FVector((1000 * i), 0, 0));

	//	AProcessPDB* protein = Cast<AProcessPDB>(UPoolManagerBPLibrary::SpawnActor(this, myProteinToSpawn, transform));
	//	protein->GenerateMoleculeColours(false);
	//	protein->SetFolder("");
	//	protein->LoadPDBfromFile("1bna");
	//}
}

// Called every frame
void APreProcess::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APreProcess::InitialiseVariables() {
	proteinPoolSize = 100;
	moleculePoolSize = 500;
}

void APreProcess::OnPoolBegin_Implementation() {
	IPoolActorInterface::OnPoolBegin_Implementation();
	// Setup the actor after getting fetched from the pool
}

void APreProcess::OnPoolEnd_Implementation() {
	IPoolActorInterface::OnPoolEnd_Implementation();
	// Set the actor to its inactive state
}

