// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointMatch.h"
#include "Molecule.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "ProcessPDB.generated.h"

USTRUCT()
struct FAlignment
{
	GENERATED_BODY()
		
	Eigen::Matrix3d rotation;
	Eigen::Vector3d translation;

	FAlignment() {
		rotation = Eigen::Matrix3d();
		translation = Eigen::Vector3d();
	}
};

USTRUCT()
struct FPairIdentifier
{
	GENERATED_BODY()

	UPROPERTY()
	FString proteinA;

	UPROPERTY()
	FString proteinB;

	UPROPERTY()
	FString folderName;

	UPROPERTY()
	int32 pairIdentifier;

	FPairIdentifier(FString folder, FString pA, FString pB) {
		folderName = folder;
		proteinA = pA;
		proteinB = pB;

		int32 hash1 = GetTypeHash(folder);
		int32 hash2 = GetTypeHash(pA);
		int32 hash3 = GetTypeHash(pB);

		pairIdentifier = HashCombine(HashCombine(hash1, hash2), hash3);
	}

	FPairIdentifier() {

	}
};

UCLASS()
class PDBIMPORTER_API AProcessPDB : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProcessPDB();

	UFUNCTION(BlueprintCallable)
	void LoadPDBfromFile(FString fileName);

	UFUNCTION(BlueprintCallable)
	void ProcessPDBWithoutRendering(FString fileName);

	//Render molecules after running the ProcessPDBWithoutRendering Function
	UFUNCTION(BlueprintCallable)
	void RenderMolecules(bool isRenderingConnections);

	UFUNCTION(BlueprintCallable)
	FString GetFileName();

	TArray<AActor*> molecules;

	TArray<AMolecule*> aMolecules;

	UPROPERTY()
	AActor* moleculeActor;

	AMolecule* moleculePointer;

	UPROPERTY()
	AActor* proteinActor;

	AProcessPDB* proteinPointer;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myMoleculeToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myProteinToSpawn;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetMolecules();

	UFUNCTION(BlueprintCallable)
	TArray<AMolecule*> GetAMolecules();

	UFUNCTION(BlueprintCallable)
	void SetFolder(FString folder);

	UFUNCTION(BlueprintCallable)
	void setFixedColours(TArray<FVector> fixedColours);

	UFUNCTION(BlueprintCallable)
	void AlignMolecules(AProcessPDB* fixedMolecules);

	UFUNCTION(BlueprintCallable)
	void AlignSingleMolecule(AProcessPDB* fixedMolecules, int32 index);

	UFUNCTION(BlueprintCallable)
	void AlignAllMoleculesBySingle(AProcessPDB* fixedMolecules, int32 index);

	UFUNCTION(BlueprintCallable)
	TArray<AMolecule*> GetAlignedMolecules(TArray<AMolecule*> fixedMolecules, TArray<AMolecule*> alignMolecules);

	UFUNCTION(BlueprintCallable)
	TArray<AMolecule*> GetAlignedMoleculesWithoutRendering(TArray<AMolecule*> alignMolecules);

	UFUNCTION(BlueprintCallable)
	TArray<AMolecule*> GetAlignedMoleculesWithoutRendering2(TArray<AMolecule*> alignMolecules, FString folder , FString proteinA, FString proteinB);

	UFUNCTION(BlueprintCallable)
    float GetSqrDisSum(TArray<AMolecule*> alignedMolecules);

	UFUNCTION(BlueprintCallable)
	void UpdateMoleculeAlignment(TArray<AMolecule*> alignedMolecules);

	UFUNCTION(BlueprintCallable)
	TArray<AProcessPDB*> GenerateBlendFrames(AProcessPDB* proteinB, int32 frames);

	UFUNCTION(BlueprintCallable)
	void GenerateMoleculeColours(bool isStatic);

	void GenerateBlendFrameColours();

	void CreateMoleculeFromPoints(FMolPositions atomPositions, int32 molIndex, AMolecule* aMol, FVector molColour);

	UFUNCTION(BlueprintCallable)
	void HideProtein(AProcessPDB* protein, bool isHidden);
	
	void HideMolecule(AMolecule* mol, bool isHidden);

	void UpdateMolecule(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex);

	AMolecule* GetUpdatedMolecule(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex);

	void GetUpdatedMoleculeWithoutRendering(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex);

	double GetSquaredDistanceSum(std::vector<std::vector<double>> fixedMol, std::vector<std::vector<double>> alignedMol);

	TArray<FMolPositions> GetAtomPositions(AProcessPDB* protein);

	FString folderName;

	FString moleculeFileName;

	TArray<FVector> colours;

	void PointMatchTest();

	PointMatch pointMatch;

	TMap<int, FAlignment> alignmentMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SaveAlignmentMapToFile(TMap<int, FAlignment> alignMap);

	void SaveProteinData();

	void LoadProteinData();

};

USTRUCT()
struct FMolPositions
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FVector> moleculePositions;

	FMolPositions() {
		moleculePositions = {};
	}
};



//USTRUCT()
//struct FAlignment
//{
//	GENERATED_BODY()
//
//	UPROPERTY()
//	Eigen::Matrix3d rotation;
//
//	UPROPERTY()
//	Eigen::Vector3d translation;
//	
//
//	FAlignment() {
//		rotation = Eigen::Matrix3d();
//		translation = Eigen::Vector3d();
//	}
//};

