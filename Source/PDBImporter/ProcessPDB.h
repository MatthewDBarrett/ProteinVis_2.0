// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointMatch.h"
#include "Molecule.h"
#include "ProcessPDB.generated.h"

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
    float GetSqrDisSum(TArray<AMolecule*> alignedMolecules);

	UFUNCTION(BlueprintCallable)
	void UpdateMoleculeAlignment(TArray<AMolecule*> alignedMolecules);

	UFUNCTION(BlueprintCallable)
	TArray<AProcessPDB*> GenerateBlendFrames(AProcessPDB* proteinB, int32 frames);

	UFUNCTION(BlueprintCallable)
	void GenerateMoleculeColours(bool isStatic);

	void CreateMoleculeFromPoints(FMolPositions atomPositions, int32 molIndex, AMolecule* aMol, FVector molColour);

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
