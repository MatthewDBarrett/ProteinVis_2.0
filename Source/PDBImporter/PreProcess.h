#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Molecule.h"
#include "ProcessPDB.h"
#include "PreProcess.generated.h"

UCLASS()
class PDBIMPORTER_API APreProcess : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreProcess();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myMoleculeToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myProteinToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myAtomMeshToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myConnectionMeshToSpawn;

	UPROPERTY()
	AActor* moleculeActor;
	UPROPERTY()
	AActor* proteinActor;
	UPROPERTY()
	AActor* atomMeshActor;
	UPROPERTY()
	AActor* connectionMeshActor;

	AMolecule* moleculePointer;
	AProcessPDB* proteinPointer;
	AInstancedStaticMeshActor* atomMeshPointer;
	ACylinderISMA* connectionMeshPointer;

	TArray<AMolecule*> moleculePool;
	TArray<AProcessPDB*> proteinPool;
	TArray<AInstancedStaticMeshActor*> atomMeshPool;
	TArray<ACylinderISMA*> connectionMeshPool;

	int32 moleculePoolSize;
	int32 proteinPoolSize;
	int32 atomMeshPoolSize;
	int32 connectionMeshPoolSize;

	FActorSpawnParameters spawnParams;
	FVector spawnPos;
	FRotator spawnRot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeVariables();

	void GenerateMoleculePool();

	void GenerateProteinPool();

	void GenerateAtomMeshPool();

	void GenerateConnectionMeshPool();

};
