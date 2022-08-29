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

		FString myFile = directory + "/" + "/PDB_Files/" + folderName + fileName + ".pdb";
		FFileHelper::LoadFileToString(atomData, *myFile);

		TArray<FString> stringRecords;
		atomData.ParseIntoArray(stringRecords, TEXT(" "), true);

		TArray<FString> moleculeStrings;

		for (int32 i = 0; i < stringRecords.Num(); i++) {

			FString segment = stringRecords[i];

			moleculeStrings.Add(segment);

			if (segment.Contains("TER") && segment.Contains("\n") && !segment.Contains("MAS")) {

				//int32 chainSize = moleculeStrings.Num()-1;
				//
				//UE_LOG(LogTemp, Warning, TEXT("0:      %s"), *moleculeStrings[0]);
				//UE_LOG(LogTemp, Warning, TEXT("1:      %s"), *moleculeStrings[1]);
				//UE_LOG(LogTemp, Warning, TEXT("2:      %s"), *moleculeStrings[2]);
				//UE_LOG(LogTemp, Warning, TEXT("3:      %s"), *moleculeStrings[3]);

				//UE_LOG(LogTemp, Warning, TEXT("%d -3:  %s"), chainSize, *moleculeStrings[chainSize-3]);
				//UE_LOG(LogTemp, Warning, TEXT("%d -2:  %s"), chainSize, *moleculeStrings[chainSize -2]);
				//UE_LOG(LogTemp, Warning, TEXT("%d -1:  %s"), chainSize, *moleculeStrings[chainSize -1]);
				//UE_LOG(LogTemp, Warning, TEXT("%d :    %s"), chainSize, *moleculeStrings[chainSize]);

				FActorSpawnParameters SpawnParams;
				FVector pos = FVector(0, 0, 0);
				FRotator rot = FRotator(0, 0, 0);

				moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
				moleculePointer = Cast<AMolecule>(moleculeActor);

				moleculePointer->SetAtomSize(1.5);			//standard 0.7f

				moleculePointer->ConvertMolecule(moleculeStrings, colours[molecules.Num()]);

				molecules.Add(moleculeActor);

				moleculeStrings = TArray<FString>();	//clear array
			}
		}
	}
}

TArray<AActor*> AProcessPDB::GetMolecules() { return molecules; }

void AProcessPDB::SetFolder(FString folder) {
	if (!folder.IsEmpty())
		folderName = folder + "/";
	else
		folderName = "";
}

void AProcessPDB::setFixedColours(TArray<FVector> fixedColours) { colours = fixedColours; }

void AProcessPDB::BeginPlay(){
	Super::BeginPlay();	
}

void AProcessPDB::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

