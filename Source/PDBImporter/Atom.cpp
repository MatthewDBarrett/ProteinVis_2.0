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

#include "Atom.h"

Atom::Atom(FString type, int32 serialNum, FString atomName, int32 branchIndicator, FString residueType, FString chainIdentifier,
	int32 residueSequenceNum, double xPos, double yPos, double zPos, FString elementSymbol) {

	this->type = type;
	this->serialNum = serialNum;
	this->atomName = atomName;
	this->branchIndicator = branchIndicator;
	this->residueType = residueType;
	this->chainIdentifier = chainIdentifier;
	this->residueSequenceNum = residueSequenceNum;
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
}

Atom::Atom(FString type, int32 serialNum, double xPos, double yPos, double zPos, FString elementSymbol) {
	this->type = type;
	this->serialNum = serialNum;
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->elementSymbol = elementSymbol;
}

Atom::~Atom() {

}

FVector Atom::GetPosition() { return FVector(xPos, yPos, zPos); }

void Atom::SetRadius(double radius) { atomRadius = radius; }

double Atom::GetRadius() { return atomRadius; }

FString Atom::GetType() { return type; }

int32 Atom::GetSerialNum() { return serialNum; }

FString Atom::GetAtomName() { return atomName; }

int32 Atom::GetBranchIndicator() { return branchIndicator; }

FString Atom::GetResidueType() { return residueType; }

FString Atom::GetChainIdentifier() { return chainIdentifier; }

int32 Atom::GetResidueSequenceNum() { return residueSequenceNum; }

double Atom::GetXPos() { return xPos; }

double Atom::GetYPos() { return yPos; }

double Atom::GetZPos() { return zPos; }

FString Atom::GetElementSymbol() { return elementSymbol; }

void Atom::SetAtomPosition(std::vector<double> position) {
	xPos = position[0];
	yPos = position[1];
	zPos = position[2];
}