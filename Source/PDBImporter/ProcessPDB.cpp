#include "ProcessPDB.h"
#include "Molecule.h"

AProcessPDB::AProcessPDB() {
	PrimaryActorTick.bCanEverTick = false;
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

				FActorSpawnParameters SpawnParams;
				FVector pos = FVector(0, 0, 0);
				FRotator rot = FRotator(0, 0, 0);

				moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
				moleculePointer = Cast<AMolecule>(moleculeActor);

				moleculePointer->SetAtomSize(0.7f);

				moleculePointer->ConvertMolecule(moleculeStrings);

				molecules.Add(moleculeActor);

				moleculeStrings = TArray<FString>();	//clear array
			}
		}
	}
}

TArray<AActor*> AProcessPDB::GetMolecules() { return molecules; }

void AProcessPDB::BeginPlay(){
	Super::BeginPlay();	
}

void AProcessPDB::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

