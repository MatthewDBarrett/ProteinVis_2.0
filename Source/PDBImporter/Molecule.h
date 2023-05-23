/**********************************************************************************
 * Molecule
 *
 * Stores the information belonging to a molecule. Handles the parsing of PDB files.
 * Additionally, computes and renders atoms and connections.
 * ________________________________________________________________________________
 *
 * This file is part of the ProteinVis project.
 *
 * Author:			Matthew Barrett
 *
 * Organisation:	University of Technology Sydney
 *
 * ProteinVis. is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * GNU General Public License V3, 29 June 2007.
 *
 * ProteinVis. is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * <https://www.gnu.org/licenses/gpl-faq.html/>
 *
 * For commercial licensing inquiries and restrictions, please contact either:
 * matthew.barrett@uts.edu.au
 * nico.pietroni@uts.edu.au
 **********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Atom.h"
#include "InstancedStaticMeshActor.h"
#include "CylinderISMA.h"
#include "Molecule.generated.h"

UCLASS()
class PDBIMPORTER_API AMolecule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMolecule();

	UFUNCTION(BlueprintCallable)
	void ConvertPDB(FString fileName);

	UFUNCTION(BlueprintCallable)
	void SetFileName(FString fileName);

	UFUNCTION(BlueprintCallable)
	void SetAtomSize(float size);

	UFUNCTION(BlueprintCallable)
	void SetPosition(FVector position);

	UFUNCTION(BlueprintCallable)
	void SetMoleculeIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	FString GetFileName();

	UFUNCTION(BlueprintCallable)
	int32 GetNumAtoms();

	UFUNCTION(BlueprintCallable)
	int32 GetNumConnections();

	UFUNCTION(BlueprintCallable)
	float GetProteinHeight();

	UFUNCTION(BlueprintCallable)
	FVector GetProteinBoundaries();

	UFUNCTION(BlueprintCallable)
	float GetProteinSize();

	void SaveCurrentAtomPositions();

	UFUNCTION(BlueprintCallable)
	AInstancedStaticMeshActor* GetAtomsPointer();

	UFUNCTION(BlueprintCallable)
	ACylinderISMA* GetConnectionsPointer();

	std::vector<std::vector<double>> GetAtomPositions();

	std::vector<std::vector<double>> GetOriginalAtomPositions();

	std::vector<std::vector<double>> GetPointMatchAlignment(AMolecule* fixedMol);

	UFUNCTION(BlueprintCallable)
	void AlignMolecule(AMolecule* fixedMol);

	void ConvertMolecule(TArray<FString> strings, FVector molColour);

	void ConvertMoleculeWithoutRendering(TArray<FString> strings);

	UFUNCTION(BlueprintCallable)
	void RenderMolecule(FVector molColour, bool isRenderingConnections);

	void CreateMoleculeFromAtoms(TArray<Atom> originalAtoms, FVector molColour, bool isRenderingConnections);

	void SetAtoms(TArray<Atom> originalAtoms);

	void SpawnAtoms();

	void SpawnSphere(FVector position, double size, FString atomName);

	void SpawnConnections();

	void SpawnCylinder(FVector atomPos1, FVector atomPos2);

	void SetProteinCentre();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> StaticMeshToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> CylinderStaticMeshToSpawn;

	void SetAtomSizes();

	UPROPERTY()
	AActor* instancedStaticMeshActor;

	UPROPERTY()
	AActor* cylinderISMA;

	void ColourChain(FVector colour);

	void SetAtomTypes();

	void SetAtomColours();

	void SpawnTempAtoms();

	void RemoveTempAtoms();

	void CreateMolecule();

	void CreateNonStandardConnections();

	TArray<Atom> GetAtoms();

	void MoveAtoms(std::vector<std::vector<double>> atomPositions, int moleculeIndex);

	FString moleculeName = "";

	int32 simulationScale = 50;

	double atomScale = 0.007f;

	int32 searchBuffer = 10;

	double connectionThickness = 1.0f;

	bool renderConnections = true;

	UFUNCTION(BlueprintCallable)
	void SetRenderConnections(bool render);

	UFUNCTION(BlueprintCallable)
	bool GetRenderConnections();
	
	bool renderHETAtoms = false;

	TArray<FString> atomTypes;

	TArray<FVector> atomColours;

	FVector proteinCentre;

	bool isConnection(Atom a, Atom b);

	TArray<FString> atomNames;
	TArray<double> atomSizes;

	AInstancedStaticMeshActor* meshPointer;

	ACylinderISMA* cylinderMeshPointer;

	bool MoleculeCreated = false;

	TArray<AActor*> tempAtoms;

	TArray<Atom> atoms;

	int32 atomCount;

	int32 connectionCount;

	int32 molIndex;

	std::vector<std::vector<double>> originalAtomPositions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
