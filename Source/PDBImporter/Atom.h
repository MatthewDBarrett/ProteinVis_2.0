/**********************************************************************************
 * Atom
 *
 * Stores the information belonging to an atom that is apart of a given molecule.
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

class Atom {

public:
	Atom(FString type, int32 serialNum, FString atomName, int32 branchIndicator, FString residueType, FString chainIdentifier,
		int32 residueSequenceNum, double xPos, double yPos, double zPos, FString elementSymbol);
	Atom(FString type, int32 serialNum, double xPos, double yPos, double zPos, FString elementSymbol);
	~Atom();

	FString GetType();
	int32 GetSerialNum();
	FString GetAtomName();
	int32 GetBranchIndicator();
	FString GetResidueType();
	FString GetChainIdentifier();
	int32 GetResidueSequenceNum();
	double GetXPos();
	double GetYPos();
	double GetZPos();
	FString GetElementSymbol();

	FVector GetPosition();

	void SetRadius(double radius);
	double GetRadius();

	void SetAtomPosition(std::vector<double> position);
	
private:
	FString type;
	int32 serialNum;
	FString atomName;
	int32 branchIndicator;
	FString residueType;
	FString chainIdentifier;
	int32 residueSequenceNum;
	double xPos;
	double yPos;
	double zPos;
	FString elementSymbol;

	double atomRadius;

};
