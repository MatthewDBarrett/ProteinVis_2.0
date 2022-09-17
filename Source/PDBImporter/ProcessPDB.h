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

	TArray<AActor*> molecules;

	UPROPERTY()
	AActor* moleculeActor;

	AMolecule* moleculePointer;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> myMoleculeToSpawn;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetMolecules();

	UFUNCTION(BlueprintCallable)
	void SetFolder(FString folder);

	UFUNCTION(BlueprintCallable)
	void setFixedColours(TArray<FVector> fixedColours);

	UFUNCTION(BlueprintCallable)
	void AlignMolecules(AProcessPDB* fixedMolecules);

	void UpdateMolecule(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex);

	FString folderName;

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
