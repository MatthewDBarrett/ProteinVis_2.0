#include "ProcessPDB.h"
#include "PointMatch.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Runtime/Engine/Public/TimerManager.h>
#include <PoolManager/Public/PoolManagerBPLibrary.h>
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
}

void AProcessPDB::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AProcessPDB::SaveAlignmentMapToFile(TMap<int, Alignment> alignmentMap) {
    // CONVERSION LOGIC
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


    return alignMolecules;
}

TArray<AMolecule*> AProcessPDB::GetAlignedMoleculesWithoutRendering2(TArray<AMolecule*> alignMolecules, FString folder, FString proteinA, FString proteinB) {
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

    FPairIdentifier identifier = FPairIdentifier(folder, proteinA, proteinB);

    if (alignmentMap.Find(identifier.pairIdentifier) == nullptr) {                          //if alignment is not currently stored in the map
        PointMatch::Alignment align = PointMatch::GetAlignment(fixedMolsPos, molsPos);
        Alignment alignmentValues = { align.rotation, align.translation };
        alignmentMap.Add(identifier.pairIdentifier, alignmentValues);
    }

    //SAVE ALIGNMENT MAP

    Alignment* alignmentValues = alignmentMap.Find(identifier.pairIdentifier);
    PointMatch::TransformRigidMatchFromStoredValues(fixedMolsPos, molsPos, alignmentValues->rotation, alignmentValues->translation);

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


    return alignMolecules;
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


