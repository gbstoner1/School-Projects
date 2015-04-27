// ***********************************************************************
//
// (c) Copyright 2014 Geoffrey Stoenr
//
//  All rights reserved.
//
// gstoner2013@fau.edu
//
// ***********************************************************************

#pragma once
#include "filenames.h"
#include <string>
using namespace std;

class XYZ_Database
{
public:
	XYZ_Database();
	string transducer(string command);
private:
	int runonce;
	filenames listoffilenames;
	filelines listoffilelines;
	BSTOfWords bsttree;
};