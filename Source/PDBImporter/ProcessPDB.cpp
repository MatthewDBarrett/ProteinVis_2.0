#include "ProcessPDB.h"
#include "PointMatch.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Runtime/Engine/Public/TimerManager.h>
#include <PoolManager/Public/PoolManagerBPLibrary.h>
#include "SaveProteinData.h"
#include "Kismet/GameplayStatics.h"
#include "multiple_match.h"
#include "CoreMinimal.h"
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

void AProcessPDB::ProcessPDBWithoutRendering(FString fileName) {

    moleculeFileName = fileName;

    aMolecules.Empty();

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

                moleculePointer->ConvertMoleculeWithoutRendering(moleculeStrings);

                aMolecules.Add(moleculePointer);

                //UE_LOG(LogTemp, Warning, TEXT("Added Molecule: %s"), *moleculePointer->GetFileName() );

                moleculeStrings = TArray<FString>();	//clear array
            }
        }
    }
}

void AProcessPDB::RenderMolecules(bool isRenderingConnections) {
    for (int i = 0; i < aMolecules.Num(); i++) {
        aMolecules[i]->RenderMolecule(colours[i], isRenderingConnections);
    }
}

FString AProcessPDB::GetFileName() { return moleculeFileName; }

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

void AProcessPDB::BeginPlay() {
    Super::BeginPlay();

    saveString = "savetest-20";
}

void AProcessPDB::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AProcessPDB::SaveAlignmentMapToFile(TMap<int, FAlignment> alignMap) {
    // CONVERSION LOGIC
}

void AProcessPDB::SaveProteinData(int key, FAlignment alignData) {
    USaveProteinData* loadInstance;
    USaveProteinData* saveInstance = Cast<USaveProteinData>(UGameplayStatics::CreateSaveGameObject(USaveProteinData::StaticClass()));

    if (UGameplayStatics::DoesSaveGameExist(saveString, 0)) {
        loadInstance = Cast<USaveProteinData>(UGameplayStatics::LoadGameFromSlot(saveString, 0));

        TMap<int, FAlignment> loadedMap = loadInstance->GetAlignmentMap();
        loadedMap.Add(key, alignData);

        saveInstance->SetAlignmentMap(loadedMap);
        saveInstance->atomAmount = this->atomAmount;

    } else {
        TMap<int, FAlignment> newMap;
        newMap.Add(key, alignData);

        saveInstance->SetAlignmentMap(newMap);
        saveInstance->atomAmount = this->atomAmount;
    }

    UGameplayStatics::SaveGameToSlot(saveInstance, saveString, 0);
}

bool AProcessPDB::LoadProteinData() {
    USaveProteinData* loadInstance;

    if (UGameplayStatics::DoesSaveGameExist(saveString, 0)) {
        loadInstance = Cast<USaveProteinData>(UGameplayStatics::LoadGameFromSlot(saveString, 0));
    } else {
        return false;
    }

    this->alignmentMap = loadInstance->GetAlignmentMap();
    this->atomAmount = loadInstance->atomAmount;

    return true;
}

TArray<AActor*> AProcessPDB::GetMolecules() { return molecules; }

TArray<AMolecule*> AProcessPDB::GetAMolecules() { return aMolecules; }

void AProcessPDB::AlignMolecules(AProcessPDB* fixedMolecules) {
    TArray<AActor*> fixedMols = fixedMolecules->GetMolecules();
    TArray<AActor*> Mols = this->GetMolecules();

    std::vector<std::vector<double>> fixedMolsPos, molsPos;

    TArray<int32> atomCounts;

    for (AActor* fixedMol : fixedMols) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
        for (std::vector<double> pos : atomPositions)
            fixedMolsPos.push_back(pos);
    }

    for (AActor* Mol : Mols) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
        atomCounts.Add(atomPositions.size());
        for (std::vector<double> pos : atomPositions)
            molsPos.push_back(pos);
    }

    //this->GetSquaredDistanceSum(fixedMolsPos, molsPos);

    PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);
    //UE_LOG(LogTemp, Warning, TEXT("fixedMolsPos: %d, molsPos: %d"), fixedMolsPos.size(), molsPos.size());

    int32 nextIndex = 0;
    for (int i = 0; i < Mols.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->UpdateMolecule(Cast<AMolecule>(Mols[i]), atomPositions, i);
        nextIndex += atomCounts[i];
    }

    this->GetSquaredDistanceSum(fixedMolsPos, molsPos);
}

void AProcessPDB::AlignSingleMolecule(AProcessPDB* fixedMolecules, int32 index) {
    TArray<AActor*> fixedMols = fixedMolecules->GetMolecules();
    TArray<AActor*> Mols = this->GetMolecules();

    std::vector<std::vector<double>> fixedMolsPos, molsPos;

    TArray<int32> atomCounts;

    std::vector<std::vector<double>> atomPositions1 = Cast<AMolecule>(fixedMols[index])->GetAtomPositions();
    for (std::vector<double> pos : atomPositions1)
        fixedMolsPos.push_back(pos);

    std::vector<std::vector<double>> atomPositions2 = Cast<AMolecule>(Mols[index])->GetAtomPositions();
    atomCounts.Add(atomPositions2.size());
    for (std::vector<double> pos : atomPositions2)
        molsPos.push_back(pos);

    PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);
    //UE_LOG(LogTemp, Warning, TEXT("fixedMolsPos: %d, molsPos: %d"), fixedMolsPos.size(), molsPos.size());

    //int32 nextIndex = 0;
    //for (int i = 0; i < index+1; i++) {
    //    std::vector<std::vector<double>> atomPositions;

    //    for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
    //        atomPositions.push_back(molsPos[j]);
    //    }

    //    this->UpdateMolecule(Cast<AMolecule>(Mols[i]), atomPositions, i);
    //    nextIndex += atomCounts[i];
    //}

    this->UpdateMolecule(Cast<AMolecule>(Mols[index]), molsPos, index);
}

void AProcessPDB::AlignAllMoleculesBySingle(AProcessPDB* fixedMolecules, int32 index) {
    TArray<AActor*> fixedMols = fixedMolecules->GetMolecules();
    TArray<AActor*> Mols = this->GetMolecules();

    std::vector<std::vector<double>> fixedMolsPos, molsPos;

    TArray<int32> atomCounts;

    std::vector<std::vector<double>> atomPositions1 = Cast<AMolecule>(fixedMols[index])->GetAtomPositions();
    for (std::vector<double> pos : atomPositions1)
        fixedMolsPos.push_back(pos);

    std::vector<std::vector<double>> atomPositions2 = Cast<AMolecule>(Mols[index])->GetAtomPositions();
    atomCounts.Add(atomPositions2.size());
    for (std::vector<double> pos : atomPositions2)
        molsPos.push_back(pos);

    PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);

    int32 nextIndex = 0;
    for (int i = 0; i < Mols.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->UpdateMolecule(Cast<AMolecule>(Mols[i]), atomPositions, i);
        nextIndex += atomCounts[i];
    }
}

TArray<AMolecule*> AProcessPDB::GetAlignedMolecules(TArray<AMolecule*> fixedMolecules, TArray<AMolecule*> alignMolecules) {

    TArray<AMolecule*> alignedMolecules;

    std::vector<std::vector<double>> fixedMolsPos, molsPos;

    TArray<int32> atomCounts;

    for (AActor* fixedMol : fixedMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
        for (std::vector<double> pos : atomPositions)
            fixedMolsPos.push_back(pos);
    }

    for (AActor* Mol : alignMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
        atomCounts.Add(atomPositions.size());
        for (std::vector<double> pos : atomPositions)
            molsPos.push_back(pos);
    }

    PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);
    //UE_LOG(LogTemp, Warning, TEXT("fixedMolsPos: %d, molsPos: %d"), fixedMolsPos.size(), molsPos.size());

    int32 nextIndex = 0;
    for (int i = 0; i < alignMolecules.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->GetUpdatedMolecule(Cast<AMolecule>(alignMolecules[i]), atomPositions, i);
        nextIndex += atomCounts[i];
    }

    return alignMolecules;
}

TArray<AMolecule*> AProcessPDB::GetAlignedMoleculesWithoutRendering(TArray<AMolecule*> alignMolecules) {
    TArray<AMolecule*> alignedMolecules;

    std::vector<std::vector<double>> fixedMolsPos, molsPos;

    TArray<int32> atomCounts;

    for (AActor* fixedMol : aMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
        for (std::vector<double> pos : atomPositions)
            fixedMolsPos.push_back(pos);
    }

    for (AActor* Mol : alignMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
        atomCounts.Add(atomPositions.size());
        for (std::vector<double> pos : atomPositions)
            molsPos.push_back(pos);
    }

    PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);

    int32 nextIndex = 0;

    for (int i = 0; i < alignMolecules.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->GetUpdatedMoleculeWithoutRendering(Cast<AMolecule>(alignMolecules[i]), atomPositions, i);
        //UE_LOG(LogTemp, Warning, TEXT("Adding Molecule: %s"), *alignMolecules[i]->GetName());

        nextIndex += atomCounts[i];
    }

    //USaveProteinData* saveInstance = Cast<USaveProteinData>(UGameplayStatics::CreateSaveGameObject(USaveProteinData::StaticClass()));

    //saveInstance->SetTestNum(42);

    //UGameplayStatics::SaveGameToSlot(saveInstance, "MySlot1", 0);


   /* USaveProteinData* loadInstance = Cast<USaveProteinData>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot1"), 0));
    UE_LOG(LogTemp, Warning, TEXT("Test Num: %d"), loadInstance->testNum);*/




    return alignMolecules;
}

TArray<AMolecule*> AProcessPDB::GetAlignedMoleculesWithoutRendering2(TArray<AMolecule*> alignMolecules, FString folder, FString proteinA, FString proteinB) {

    TArray<AMolecule*> alignedMolecules;

    FPairIdentifier identifier = FPairIdentifier(folder, proteinA, proteinB);
    std::vector<std::vector<double>> fixedMolsPos, molsPos;
    
    this->LoadProteinData();

    bool alignmentFound = false;

    FAlignment alignmentValues;

    atomAmount.Empty();

    if (alignmentMap.Num() > 0) {                                                               //Previously saved alignments have been found
        UE_LOG(LogTemp, Warning, TEXT("Previously saved alignments have been found"));
        if (alignmentMap.Find(identifier.pairIdentifier) == nullptr) {                          //if alignment is not currently stored in the map
            UE_LOG(LogTemp, Warning, TEXT("current alignment not found in stored map"));
        } else {                                                                                //Existing alignment found for pair
            UE_LOG(LogTemp, Warning, TEXT("Existing alignment found for pair"));
            alignmentFound = true;
        }
    } else {                                                                                    //No Previously saved alignments
        UE_LOG(LogTemp, Warning, TEXT("No previously saved alignments"));
    }

    if (!alignmentFound) {
        for (AActor* fixedMol : aMolecules) {
            std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
            for (std::vector<double> pos : atomPositions)
                fixedMolsPos.push_back(pos);
        }

        for (AActor* Mol : alignMolecules) {
            std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
            atomAmount.Add(atomPositions.size());
            for (std::vector<double> pos : atomPositions)
                molsPos.push_back(pos);
        }

        //PointMatch::Alignment align = PointMatch::GetAlignment(fixedMolsPos, molsPos);
        //alignmentValues.rotation = align.rotation;
        //alignmentValues.translation = align.translation;
        alignmentMap.Add(identifier.pairIdentifier, alignmentValues);
    } else {
        alignmentValues = *alignmentMap.Find(identifier.pairIdentifier);
        //PointMatch::TransformRigidMatchFromStoredValues(fixedMolsPos, molsPos, alignmentValues.rotation, alignmentValues.translation);
    }

    if (atomAmount.Num() == 0) {
        for (AActor* Mol : alignMolecules) {
            std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
            atomAmount.Add(atomPositions.size());
        }
    }

    this->SaveProteinData(identifier.pairIdentifier, alignmentValues);

    int32 nextIndex = 0;

    for (int i = 0; i < alignMolecules.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomAmount[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->GetUpdatedMoleculeWithoutRendering(Cast<AMolecule>(alignMolecules[i]), atomPositions, i);

        nextIndex += atomAmount[i];
    }
        
    return alignMolecules;
}

TArray<AMolecule*> AProcessPDB::GetAlignedMoleculesWithoutRendering3(TArray<AMolecule*> alignMolecules, FString folder, FString proteinA, FString proteinB) {

    //std::vector<std::vector<double>> fixedMolsPos, molsPos;

    //atomAmount.Empty();
    //
    //FPairIdentifier identifier = FPairIdentifier(folder, proteinA, proteinB);
    //FAlignment alignmentValues;
    //bool alignmentFound = false;    

    //for (AActor* fixedMol : aMolecules) {
    //    std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
    //    for (std::vector<double> pos : atomPositions)
    //        fixedMolsPos.push_back(pos);
    //}

    //for (AActor* Mol : alignMolecules) {
    //    std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
    //    atomAmount.Add(atomPositions.size());
    //    for (std::vector<double> pos : atomPositions)
    //        molsPos.push_back(pos);
    //}

    //if (this->LoadProteinData()) {
    //    UE_LOG(LogTemp, Warning, TEXT("previous saves found - %d - %d"), alignmentMap.Num(), identifier.pairIdentifier);
    //    if (alignmentMap.Find(identifier.pairIdentifier) != nullptr) {
    //        FAlignment* fVal = alignmentMap.Find(identifier.pairIdentifier);
    //        PointMatch::TransformRigidMatchFromStoredValues(fixedMolsPos, molsPos, fVal->rotation, fVal->translation);
    //        alignmentFound = true;

    //        UE_LOG(LogTemp, Warning, TEXT("alignment found - %d"), identifier.pairIdentifier);
    //    }   
    //}

    //if (!alignmentFound) {
    //    PointMatch::Alignment align = PointMatch::GetAlignment(fixedMolsPos, molsPos);
    //    //PointMatch::TrasformRigidMatch(fixedMolsPos, molsPos);
    //    
    //    alignmentValues.rotation = align.rotation;
    //    alignmentValues.translation = align.translation;

    //    //PointMatch::TransformRigidMatchFromStoredValues(fixedMolsPos, molsPos, alignmentValues.rotation, alignmentValues.translation);

    //    //this->SaveProteinData(identifier.pairIdentifier, alignmentValues);
    //}

    //int32 nextIndex = 0;

    //for (int i = 0; i < alignMolecules.Num(); i++) {
    //    std::vector<std::vector<double>> atomPositions;
    //    for (int j = nextIndex; j < nextIndex + atomAmount[i]; j++) {
    //        atomPositions.push_back(molsPos[j]);
    //    }

    //    this->GetUpdatedMoleculeWithoutRendering(Cast<AMolecule>(alignMolecules[i]), atomPositions, i);

    //    nextIndex += atomAmount[i];
    //}

    return alignMolecules;
}

void AProcessPDB::MultiMatchTest() {
    size_t curr_label;
    double curr_error;
    std::vector<std::vector<double > > TransfPoint;

    for (int i = 0; i < storedProteins.Num(); i++) {
        MMatch.GetSurtedSequencePoint(0, i, curr_label, curr_error, TransfPoint);
        UE_LOG(LogTemp, Warning, TEXT("Label: %d  error: %f"), curr_label, curr_error);
    }
}

void AProcessPDB::InitMultiMatchFromProteins(TArray<AProcessPDB*> proteins) {
    storedProteins = proteins;

    std::vector<std::vector<std::vector<double>>> PClouds;
    proteinCount = proteins.Num();

    int32 proteinsNum = proteins.Num();
    int32 moleculeNum = 0;
    atomCountsPerMol.Empty();
    AMolecule* mol;
    TArray<AMolecule*> mols;
    std::vector<std::vector<double>> atomPositions;

    PClouds.resize(proteinsNum);

    int atomCount = 0;

    for (int i = 0; i < proteinsNum; i++) {
        mols = proteins[i]->GetAMolecules();
        moleculeNum = mols.Num();

        atomCount = 0;

        for (int j = 0; j < moleculeNum; j++) {
            mol = mols[j];

            if (i == 0) {
                atomCountsPerMol.Add(mol->atoms.Num());
            }

            atomPositions = Cast<AMolecule>(mol)->GetAtomPositions();

            for (int m = 0; m < atomPositions.size(); m++) {
                PClouds[i].resize(atomCount + 1);

                std::vector<double> pos = atomPositions[m];
                if (pos.size() > 0) {
                    PClouds[i][atomCount].push_back(pos[0]);
                    PClouds[i][atomCount].push_back(pos[1]);
                    PClouds[i][atomCount].push_back(pos[2]);
                }
                atomCount++;
            }
        }
    }

    //for (int i = 0; i < PClouds.size(); i++) {
    //    UE_LOG(LogTemp, Warning, TEXT("Protein"));
    //    for (int j = 0; j < PClouds[i].size(); j++) {
    //        UE_LOG(LogTemp, Warning, TEXT("Atom"));
    //        for (int m = 0; m < PClouds[i][j].size(); m++) {
    //            UE_LOG(LogTemp, Warning, TEXT("pos: %f , %f , %f"), PClouds[i][j][0], PClouds[i][j][1], PClouds[i][j][2]);
    //        }
    //    }
    //}

    MMatch.InitMatches(PClouds);
}

TArray<AProcessPDB*> AProcessPDB::GetNearestMatchProteins(int32 target) {
    size_t curr_label;
    double curr_error;
    std::vector<std::vector<double > > TransfPoint;

    std::vector<std::vector<std::vector<std::vector<double > >>> proteinCloud;              //Proteins, Molecules, Atoms, Positions

    AProcessPDB* selectedProtein;

    proteinCloud.resize(storedProteins.Num());

    for (int i = 0; i < storedProteins.Num(); i++) {
        MMatch.GetSurtedSequencePoint(0, i, curr_label, curr_error, TransfPoint);

        selectedProtein = storedProteins[curr_label];

        int atomCount = TransfPoint.size();

        proteinCloud[i].resize(selectedProtein->GetAMolecules().Num());

        int count = 0;
        int atomsInMol = 1;

        proteinCloud[i][0].resize(atomCountsPerMol[0]);

        for (int j = 0; j < atomCount; j++) {
            
            if (atomsInMol - 1 == atomCountsPerMol[count]) {
                count++;
                atomsInMol = 1;
                proteinCloud[i][count].resize(atomCountsPerMol[count]);                      
            }
            
            proteinCloud[i][count][atomsInMol - 1].push_back(TransfPoint[j][0]);
            proteinCloud[i][count][atomsInMol - 1].push_back(TransfPoint[j][1]);
            proteinCloud[i][count][atomsInMol - 1].push_back(TransfPoint[j][2]);

            atomsInMol++;
        }
    }



    for (int i = 0; i < storedProteins.Num(); i++) {
        selectedProtein = storedProteins[i];

        TArray<AMolecule*> mols = selectedProtein->GetAMolecules();

        for (int j = 0; j < mols.Num(); j++) {
            std::vector<std::vector<double>> atomPositions = proteinCloud[i][j];

            this->GetUpdatedMoleculeWithoutRendering(mols[j], atomPositions, 0);
        }
    }

    return storedProteins;
}

TArray<int> AProcessPDB::GetNearestProteinsByIndex(int32 targetIndex) {
    TArray<int> nearestProteins;

    size_t curr_label;
    double curr_error;
    std::vector<std::vector<double > > TransfPoint;

    for (int i = 0; i < proteinCount; i++) {
        MMatch.GetSurtedSequencePoint(0, i, curr_label, curr_error, TransfPoint);
        nearestProteins.Add(curr_label);
    }

    return nearestProteins;
}

float AProcessPDB::GetSqrDisSum(TArray<AMolecule*> alignedMolecules) {
    
    //UE_LOG(LogTemp, Warning, TEXT("OG fixed: %d"), fixedMolecules.Num());
    
    std::vector<std::vector<double>> fixedMolsPos, molsPos;
    
    for (AActor* fixedMol : aMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(fixedMol)->GetAtomPositions();
        for (std::vector<double> pos : atomPositions)
            fixedMolsPos.push_back(pos);
    }

    for (AActor* Mol : alignedMolecules) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
        for (std::vector<double> pos : atomPositions)
            molsPos.push_back(pos);
    }

    //UE_LOG(LogTemp, Warning, TEXT("fixed: %d mols: %d"), fixedMolsPos.size(), molsPos.size());

    return this->GetSquaredDistanceSum(fixedMolsPos, molsPos);
}

void AProcessPDB::UpdateMoleculeAlignment(TArray<AMolecule*> alignedMolecules) {

    TArray<AMolecule*> Mols = alignedMolecules;
    TArray<int32> atomCounts;
    std::vector<std::vector<double>> molsPos;
    
    for (AActor* Mol : Mols) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(Mol)->GetAtomPositions();
        atomCounts.Add(atomPositions.size());
        for (std::vector<double> pos : atomPositions)
            molsPos.push_back(pos);
    }

    int32 nextIndex = 0;
    for (int i = 0; i < Mols.Num(); i++) {
        std::vector<std::vector<double>> atomPositions;

        for (int j = nextIndex; j < nextIndex + atomCounts[i]; j++) {
            atomPositions.push_back(molsPos[j]);
        }

        this->UpdateMolecule(Cast<AMolecule>(Mols[i]), atomPositions, i);
        nextIndex += atomCounts[i];
    }
}

TArray<AProcessPDB*> AProcessPDB::GenerateBlendFrames(AProcessPDB* proteinB, int32 frames) {
    TArray<AProcessPDB*> blendedProteins;

    TArray<FMolPositions> proteinAPositions = this->GetAtomPositions(this);
    TArray<FMolPositions> proteinBPositions = this->GetAtomPositions(proteinB);

    this->GenerateMoleculeColours(true);
    this->RenderMolecules(false);
    blendedProteins.Add(this);

    FTimerHandle handle;

    FTransform transform = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0));

    for (int i = 0; i < frames; i++) {

        AProcessPDB* protein = Cast<AProcessPDB>(UPoolManagerBPLibrary::SpawnActor(this, myProteinToSpawn, transform));
        protein->GenerateMoleculeColours( true );
        //protein->GenerateBlendFrameColours();

        for (int j = 0; j < this->GetAMolecules().Num(); j++) {                         //Each iteration is another molecule within a protein
            FMolPositions positions;

            for (int m = 0; m < this->GetAMolecules()[j]->GetNumAtoms(); m++) {         //Each atom position within a molecule
                double x1 = proteinAPositions[j].moleculePositions[m].X;
                double y1 = proteinAPositions[j].moleculePositions[m].Y;
                double z1 = proteinAPositions[j].moleculePositions[m].Z;

                double x2 = proteinBPositions[j].moleculePositions[m].X;
                double y2 = proteinBPositions[j].moleculePositions[m].Y;
                double z2 = proteinBPositions[j].moleculePositions[m].Z;

                double newX = x1 + (((x2 - x1) / (frames + 1)) * (i + 1));
                double newY = y1 + (((y2 - y1) / (frames + 1)) * (i + 1));
                double newZ = z1 + (((z2 - z1) / (frames + 1)) * (i + 1));

                positions.moleculePositions.Add(FVector(newX, newY, newZ)); 
            }

            protein->CreateMoleculeFromPoints(positions, j, this->GetAMolecules()[j], protein->colours[j]);
        }
        blendedProteins.Add(protein);
    }

    proteinB->GenerateMoleculeColours(true);
    proteinB->RenderMolecules(false);
    proteinB->HideProtein(proteinB, true);

    blendedProteins.Add(proteinB);

    return blendedProteins;
}

void AProcessPDB::GenerateMoleculeColours(bool isStatic) {
    if (isStatic) {
        colours.Add(FVector(96, 207, 255));
        colours.Add(FVector(105, 71, 255));
        colours.Add(FVector(255, 73, 230));
    } else {
        colours.Add(FVector(FMath::RandRange(0,255), FMath::RandRange(0, 255), FMath::RandRange(0, 255)));
        colours.Add(FVector(FMath::RandRange(0, 255), FMath::RandRange(0, 255), FMath::RandRange(0, 255)));
        colours.Add(FVector(FMath::RandRange(0, 255), FMath::RandRange(0, 255), FMath::RandRange(0, 255)));
    }
}

void AProcessPDB::GenerateBlendFrameColours(){
    colours.Add(FVector(136, 193, 218));
    colours.Add(FVector(103, 86, 180));
    colours.Add(FVector(201, 108, 188));
}

void AProcessPDB::CreateMoleculeFromPoints(FMolPositions atomPositions, int32 molIndex, AMolecule* aMol, FVector molColour) {

    FTransform transform = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0));

    AMolecule* molecule = Cast<AMolecule>(UPoolManagerBPLibrary::SpawnActor(this, myMoleculeToSpawn, transform));

    molecule->SetAtomSize(1.5);			//standard 0.7f

    TArray<Atom> molAtoms = aMol->GetAtoms();
    
    for (int i = 0; i < molAtoms.Num(); i++) {
        
        std::vector<double> newPos = { atomPositions.moleculePositions[i].X, atomPositions.moleculePositions[i].Y, atomPositions.moleculePositions[i].Z };
        molAtoms[i].SetAtomPosition( newPos );
    }
    
    molecule->CreateMoleculeFromAtoms(molAtoms, molColour, false);
    aMolecules.Add(molecule);
    this->HideMolecule(molecule, true);
}

void AProcessPDB::HideProtein(AProcessPDB* protein, bool isHidden) {
    TArray<AMolecule*> mols = protein->GetAMolecules();
    for (AMolecule* bMol : mols)
        protein->HideMolecule(bMol, isHidden);
}

void AProcessPDB::HideMolecule(AMolecule* mol, bool isHidden){
    mol->GetAtomsPointer()->SetActorHiddenInGame(isHidden);
    mol->GetConnectionsPointer()->SetActorHiddenInGame(isHidden);
}

void AProcessPDB::UpdateMolecule(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex) {
    for (int i = 0; i < mol->atoms.Num(); i++)
        mol->atoms[i].SetAtomPosition(atomPositions[i]);

    //mol->meshPointer->RemoveAllAtoms();

    FActorSpawnParameters SpawnParams;
    FVector pos = FVector(0, 0, 0);
    FRotator rot = FRotator(0, 0, 0);

    moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
    moleculePointer = Cast<AMolecule>(moleculeActor);

    moleculePointer->SetAtomSize(1.5);			//standard 0.7f

    moleculePointer->CreateMoleculeFromAtoms(mol->atoms, colours[molIndex], false);

    moleculePointer->SetPosition(FVector(12000, 0, 0));

    //mol->ColourChain( colours[molIndex] );

    /*for (int i = 0; i < atomPositions.size(); i++) {
        mol->meshPointer->SetCustomData(i, 0, colours[molIndex].X / 255, true);

        mol->meshPointer->SetCustomData(i, 1, colours[molIndex].Y / 255, true);

        mol->meshPointer->SetCustomData(i, 2, colours[molIndex].Z / 255, true);
    }*/

    /*mol->SetProteinCentre();

    mol->SpawnAtoms();*/
}

AMolecule* AProcessPDB::GetUpdatedMolecule(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex) {
    for (int i = 0; i < mol->atoms.Num(); i++)
        mol->atoms[i].SetAtomPosition(atomPositions[i]);

    //mol->meshPointer->RemoveAllAtoms();

    FActorSpawnParameters SpawnParams;
    FVector pos = FVector(0, 0, 0);
    FRotator rot = FRotator(0, 0, 0);

    moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
    moleculePointer = Cast<AMolecule>(moleculeActor);

    moleculePointer->SetAtomSize(1.5);			//standard 0.7f

    moleculePointer->CreateMoleculeFromAtoms(mol->atoms, colours[molIndex], false);

    moleculePointer->SetPosition(FVector(12000, 0, 0));

    return moleculePointer;
}

void AProcessPDB::GetUpdatedMoleculeWithoutRendering(AMolecule* mol, std::vector<std::vector<double>> atomPositions, int32 molIndex) {
    for (int i = 0; i < mol->atoms.Num(); i++)
        mol->atoms[i].SetAtomPosition(atomPositions[i]);

    ////mol->meshPointer->RemoveAllAtoms();

    //FActorSpawnParameters SpawnParams;
    //FVector pos = FVector(0, 0, 0);
    //FRotator rot = FRotator(0, 0, 0);

    //moleculeActor = GetWorld()->SpawnActor<AActor>(myMoleculeToSpawn, pos, rot, SpawnParams);
    //moleculePointer = Cast<AMolecule>(moleculeActor);

    //moleculePointer->SetAtoms(mol->atoms);
}

double AProcessPDB::GetSquaredDistanceSum(std::vector<std::vector<double>> fixedMol, std::vector<std::vector<double>> alignedMol) {
    double sum = 0;

    for (int i = 0; i < fixedMol.size(); i++) {
        sum += (pow(alignedMol[i][0] - fixedMol[i][0], 2) +
            pow(alignedMol[i][1] - fixedMol[i][1], 2) +
            pow(alignedMol[i][2] - fixedMol[i][2], 2) );
    }
    
    return sum;
}

TArray<FMolPositions> AProcessPDB::GetAtomPositions(AProcessPDB* protein) {
    TArray<AMolecule*> mols = protein->GetAMolecules();
    TArray<FMolPositions> proteinPositions;

    for (AMolecule* mol : mols) {
        std::vector<std::vector<double>> atomPositions = Cast<AMolecule>(mol)->GetAtomPositions();
        FMolPositions molPositions;
        for (std::vector<double> pos : atomPositions)
            molPositions.moleculePositions.Add(FVector(pos[0], pos[1], pos[2]));

        proteinPositions.Add(molPositions);
    }

    return proteinPositions;
}


