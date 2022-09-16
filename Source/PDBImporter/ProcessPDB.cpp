#include "ProcessPDB.h"
#include "PointMatch.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "Molecule.h"

AProcessPDB::AProcessPDB() {
	PrimaryActorTick.bCanEverTick = false;
}

void AProcessPDB::LoadPDBfromFile(FString fileName) {

    //this->PointMatchTest();

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

void AProcessPDB::PointMatchTest() {
	//const std::vector<Eigen::Vector3d> pFix;
	//std::vector<Eigen::Vector3d> pMov;
	//Eigen::Matrix3d R;
	//Eigen::Vector3d t;

	//pointMatch = PointMatch();
	////pointMatch.TrasformRigidMatch(&pFix, &pMov);

	std::vector<std::vector<double> > PFix, PMov;

    //INITIALIZE 8 POINTS OF A CUBE

    // point 0,0,0

    std::vector<double> P0;

    P0.push_back(0);//X of a point

    P0.push_back(0);//Y of a point

    P0.push_back(0);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P0);



    // point 0,1,0

    std::vector<double> P1;

    P1.push_back(0);//X of a point

    P1.push_back(1);//Y of a point

    P1.push_back(0);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P1);



    // point 1,0,0

    std::vector<double> P2;

    P2.push_back(1);//X of a point

    P2.push_back(0);//Y of a point

    P2.push_back(0);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P2);



    // point 1,1,0

    std::vector<double> P3;

    P3.push_back(1);//X of a point

    P3.push_back(1);//Y of a point

    P3.push_back(0);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P3);



    // point 0,0,1

    std::vector<double> P4;

    P4.push_back(0);//X of a point

    P4.push_back(0);//Y of a point

    P4.push_back(1);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P4);



    // point 0,1,1

    std::vector<double> P5;

    P5.push_back(0);//X of a point

    P5.push_back(1);//Y of a point

    P5.push_back(1);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P5);



    // point 1,0,1

    std::vector<double> P6;

    P6.push_back(1);//X of a point

    P6.push_back(0);//Y of a point

    P6.push_back(1);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P6);



    // point 1,1,1

    std::vector<double> P7;

    P7.push_back(1);//X of a point

    P7.push_back(1);//Y of a point

    P7.push_back(1);//Z of a point

    //add the point to the set of all points

    PFix.push_back(P7);


    //THEN COPY THE CUBE

    PMov = PFix;

    //translate along the X of 0.3 all the points

    PMov[0][0] += 0.3;

    PMov[1][0] += 0.3;

    PMov[2][0] += 0.3;

    PMov[3][0] += 0.3;

    PMov[4][0] += 0.3;

    PMov[5][0] += 0.3;

    PMov[6][0] += 0.3;

    PMov[7][0] += 0.3;


    /*std::cout << std::fixed;

    std::cout << std::setprecision(2);*/


    UE_LOG(LogTemp, Warning, TEXT("POSITIONS BEFORE POINT MATCH"));

    for (size_t i = 0; i < PMov.size(); i++)
        UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f ,"), PMov[i][0], PMov[i][1], PMov[i][2]);

    PointMatch::TrasformRigidMatch(PFix, PMov);

    UE_LOG(LogTemp, Warning, TEXT("POSITIONS AFTER POINT MATCH"));

    for (size_t i = 0; i < PMov.size(); i++)
        UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f ,"), PMov[i][0], PMov[i][1], PMov[i][2]);
}

void AProcessPDB::BeginPlay(){
	Super::BeginPlay();	
}

void AProcessPDB::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}
