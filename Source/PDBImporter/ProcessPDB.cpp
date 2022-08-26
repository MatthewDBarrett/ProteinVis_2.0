// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessPDB.h"
#include "Molecule.h"

// Sets default values
AProcessPDB::AProcessPDB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AProcessPDB::LoadPDBfromFile(FString fileName) {

	FString directory = FPaths::ProjectContentDir();
	FString atomData;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + "/PDB_Files/" + fileName + ".pdb";
		FFileHelper::LoadFileToString(atomData, *myFile);

		TArray<FString> stringRecords;
		atomData.ParseIntoArray(stringRecords, TEXT(" "), true);

		TArray<FString> moleculeStrings;

		for (int32 i = 0; i < stringRecords.Num(); i++) {

			FString segment = stringRecords[i];

			moleculeStrings.Add(segment);

			if (segment.Contains("TER") && segment.Len() <= 5) {
				//UE_LOG(LogTemp, Warning, TEXT("///////////////////////////////////////////////////////////////////"), );
				for (FString s : moleculeStrings) {
					//UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
				}
				//UE_LOG(LogTemp, Warning, TEXT("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"), );

				FActorSpawnParameters SpawnParams;
				FVector pos = FVector(0, 0, 0);
				FRotator rot = FRotator(0, 0, 0);

				moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
				moleculePointer = Cast<AMolecule>(moleculeActor);

				moleculePointer->SetAtomSize(0.7f);

				moleculePointer->ConvertMolecule(moleculeStrings);

				molecules.Add(moleculeActor);

				moleculeStrings = TArray<FString>();	//clear array
			} else {
				//moleculeStrings.Add(segment);
			}
		}
	}
}

TArray<AActor*> AProcessPDB::GetMolecules() { return molecules; }

// Called when the game starts or when spawned
void AProcessPDB::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProcessPDB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

